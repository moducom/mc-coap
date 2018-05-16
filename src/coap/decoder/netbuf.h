#pragma once

#include "coap/decoder.h"
#include "coap-token.h"
#include <estd/string.h>

namespace moducom { namespace coap {

template <class TNetBuf>
class experimental_option_iterator;

// standalone Decoder works well enough, so this is largely just a netbuf-capable
// wrapper around it
template <class TNetBuf>
class NetBufDecoder : public Decoder
{
    typedef TNetBuf netbuf_t;
    typedef Decoder base_t;
    typedef moducom::pipeline::MemoryChunk::readonly_t ro_chunk_t;

    friend class experimental_option_iterator<TNetBuf>;

protected:
    netbuf_t m_netbuf;
    // FIX: intermediate chunk until context has a value instead of a ref for its chunk
    ro_chunk_t chunk;
    Context context;

public:
    bool process_iterate()
    {
        // TODO: Will know how to advance through netbuf
        return base_t::process_iterate(context);
    }

protected:
    void process_option_header_experimental()
    {
        ASSERT_WARN(Decoder::Options, state(), "Must be in options processing mode");

        process_iterate();

        ASSERT_WARN(OptionDecoder::ValueStart, option_decoder().state(), "Must be at OptionValueStart");
    }

    // NOTE: Actually shaping up to be an internal call, because we always want
    // to move past OptionValueDone when evaluating/processing options and this
    // call does not do that
    // NOTE: May not be so useful or interesting after all, since option_number
    // and option_length are so readily available
    bool process_option_header_experimental(Option::Numbers* number, uint16_t* length)
    {
        process_option_header_experimental();

        (int&)(*number) += option_number();
        *length = option_length();

        return true;
    }

    // simulate processed memory chunk behavior here (like unprocessed,
    // but in this case const applies)
    const uint8_t* unevaluated() const
    {
        return context.chunk.data(context.pos);
    }

    // see above
    size_t length_unevaluated() const
    {
        return context.chunk.length() - context.pos;
    }

    // internal call , needs to be mated to process_option_header_experimental
    ro_chunk_t process_option_value_experimental(bool* partial = NULLPTR)
    {
        ASSERT_WARN(Decoder::Options, state(), "Must be in options processing mode");

        // assert that we are at ValueStart or OptionValue (latter when chunked)
        ASSERT_WARN(OptionDecoder::ValueStart, option_decoder().state(), "Must be at ValueStart");

        // NOTE: Safe to grab this, option_decoder().option_length() doesn't get clobbered for a while still
        int value_length = option_decoder().option_length();
        const uint8_t* raw = context.chunk.data(context.pos);
        int actual_remaining_length = context.chunk.length() - context.pos;
        bool _partial = value_length > actual_remaining_length;

        if(partial != NULLPTR) *partial = _partial;

        // it's implied there's another chunk coming if value_length
        // exceeds actual_remaining_length
        if(_partial)
            return ro_chunk_t(raw, actual_remaining_length);
        else
            return ro_chunk_t(raw, value_length);
    }

public:
    NetBufDecoder(const netbuf_t& netbuf) :
        m_netbuf(netbuf),
        chunk(netbuf.processed(), netbuf.length_processed()),
        // NOTE: Be advised that netbuf.end() differs from traditional iterator end
        // in that it is a bool indicating that we are ON the last chunk, not PAST it
        context(chunk, netbuf.end())
    {}

    netbuf_t& netbuf() { return m_netbuf; }

    // keep processing until we encounter state
    // keep processing for max_attempts
    // able to do this because netbuf is able to provide *all* of interested incoming buffers
    // where core decoder though it knows whether it's the last chunk, it doesn't know how
    // to retrieve the next one
    // in debug mode, this should indicate an error if we never reach said state
    bool process_until_experimental(Decoder::State s, int max_attempts = 50)
    {
        while(max_attempts-- > 0)
        {
            if(state() != s)
            {
                process_iterate();
            }
            else
                return true;
        }

        // TODO: Reveal error that we couldn't find state s
        ASSERT_ERROR(false, true, "Unable to find requested state");
        return false;
    }

    coap::Header process_header_experimental()
    {
        ASSERT_WARN(Decoder::Uninitialized, state(), "Expected to be at beginning of decoder processing");

        process_until_experimental(Decoder::HeaderDone);

        return header_decoder();
    }


    // TODO: Ensure this is a non-blocking call and return true or false denoting
    // whether we've reached a blocking point, not whether we got a nonzero tkl
    bool process_token_experimental(layer2::Token* token)
    {
        ASSERT_WARN(Decoder::HeaderDone, state(), "Expected to be at end of header processing");

        int tkl = header_decoder().token_length();

        // NOTE: Can't 100% remember if TokenDone is triggered on a 0-length token
        process_until_experimental(Decoder::TokenDone);

        if(tkl > 0)
        {
            new (token) layer2::Token(token_decoder().data(), tkl);
            return true;
        }
        else return false;
    }

    layer3::Token process_token_experimental()
    {
        ASSERT_WARN(Decoder::HeaderDone, state(), "Expected to be at end of header processing");

        int tkl = header_decoder().token_length();

        // NOTE: Can't 100% remember if TokenDone is triggered on a 0-length token
        process_until_experimental(Decoder::TokenDone);

        return layer3::Token(token_decoder().data(), tkl);
    }

    // kicks off option processing
    bool begin_option_experimental()
    {
        ASSERT_WARN(Decoder::TokenDone, state(), "Must be at end of token processing");

        // move us into OptionsStart
        process_iterate();
        // move us into Options or OptionsDone
        process_iterate();

        // expected to be at DeltaAndLengthDone here
        return true;
    }


    void option_next_experimental()
    {
        // move forward past value portion / past option value start
        process_iterate();

        ASSERT_WARN(Option::OptionValueDone, option_decoder().state(), "Unexpected state");

        // move past option value done.  NOTE this actually moves into domain of next option,
        // OR moves right by OptionsDone
        // expected to be at DeltaAndLengthDone here
        process_iterate();
    }

    const estd::layer3::basic_string<const char, false> option_string_experimental(bool* partial = NULLPTR)
    {
        uint16_t length = option_decoder().option_length();

        ro_chunk_t option_value = process_option_value_experimental(partial);

        const estd::layer3::basic_string<const char, false> s(length,
                                                        (const char*) option_value.data(), length);

        return s;
    }
};


// Neat, but right way to do this would be to make a 'super' OptionsDecoder which had a bit
// of the start-stop condition awareness of full Decoder, then actually derive from that class
// so that we can do things like postfix++
template <class TNetBuf>
class experimental_option_iterator
{
    typedef NetBufDecoder<TNetBuf> decoder_t;
    typedef Option::Numbers value_type;

    decoder_t& decoder;

    void partial_advance_and_get_number()
    {
        using namespace moducom::coap;

        decoder.process_option_header_experimental();

        value_type number = (value_type) decoder.option_number();

#ifdef FEATURE_ESTD_IOSTREAM_NATIVE
        std::clog << "Option: ";// << number;
        ::operator <<(std::clog, number); // why do I have to do this??
#endif
    }

public:
    experimental_option_iterator(decoder_t& decoder, bool begin_option = false) :
        decoder(decoder)
    {
        // NOT repeatable
        if(begin_option)
            decoder.begin_option_experimental();

        partial_advance_and_get_number();
    }


    bool valid() const
    {
        return decoder.state() == Decoder::Options;
    }

    experimental_option_iterator& operator ++()
    {
        decoder.option_next_experimental();
        if(valid())
        {
#ifdef FEATURE_ESTD_IOSTREAM_NATIVE
            std::clog << std::endl;
#endif
            partial_advance_and_get_number();
        }
        else
        {
#ifdef FEATURE_ESTD_IOSTREAM_NATIVE
            std::clog << std::endl;
#endif
        }

        return *this;
    }

    /* disabling postfix version because things like basic_string would be out of sync.
     * could also be problematic with chunked netbufs
    experimental_option_iterator operator ++(int)
    {
        experimental_option_iterator temp(decoder, number);
        operator ++();
        return temp;
    } */

    operator value_type()
    {
        return (value_type) decoder.option_number();
    }

    estd::layer3::basic_string<const char, false> string()
    {
        using namespace moducom::coap;

        estd::layer3::basic_string<const char, false> s = decoder.option_string_experimental();

#ifdef FEATURE_ESTD_IOSTREAM_NATIVE
        std::clog << " (";
        ::operator <<(std::clog, s);
        std::clog << ')';
#endif
        return s;
    }

};

}}
