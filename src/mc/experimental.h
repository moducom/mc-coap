//
// Created by malachi on 12/29/17.
//
// Code that is too experimental to live alongside other code

#ifndef MC_COAP_TEST_EXPERIMENTAL_H
#define MC_COAP_TEST_EXPERIMENTAL_H

#include "../platform.h"
#include "../coap-encoder.h"
#include "pipeline-writer.h"


namespace moducom { namespace coap { namespace experimental {

class BufferedEncoderBase
{
protected:
    //typedef CoAP::ParserDeprecated::State state_t;
    //typedef CoAP::ParserDeprecated _state_t;
    typedef experimental::root_state_t state_t;
    typedef experimental::_root_state_t _state_t;

    state_t state;
};

// NOTE: very experimental.  Seems to burn up more memory and cycles than it saves
// this attempts to buffer right within IBufferedPipelineWriter itself
// TODO: Use StateHelper for this
class BufferedEncoder
{
    //typedef CoAP::OptionExperimentalDeprecated::Numbers number_t;
    //typedef CoAP::ParserDeprecated::State state_t;
    //typedef CoAP::ParserDeprecated _state_t;
    typedef experimental::option_number_t number_t;
    typedef experimental::root_state_t state_t;
    typedef experimental::_root_state_t _state_t;


    pipeline::IBufferedPipelineWriter& writer;

    // TODO: We could union-ize buffer and optionEncoder, since buffer
    // primarily serves header and token
    pipeline::MemoryChunk buffer;
    ExperimentalPrototypeBlockingOptionEncoder1 optionEncoder;

    state_t state;

    // ensure header and token are advanced past
    void flush_token(state_t s)
    {
        if(state == _state_t::Header)
        {
            size_t pos = 4 + header()->token_length();
            writer.advance_write(pos, Root::boundary_segment);
        }

        state = s;
    }

public:
    // acquire header for external processing
    Header* header()
    {
        return reinterpret_cast<Header*>(buffer.data());
    }


    BufferedEncoder(pipeline::IBufferedPipelineWriter& writer) :
            state(_state_t::Header),
            writer(writer)
    {
        CONSTEXPR size_t minimum_length = (sizeof(Header) + sizeof(layer1::Token));

        buffer = writer.peek_write(minimum_length);

        header()->raw = 0;

        ASSERT_ERROR(true, buffer.length() >= minimum_length,
                     "Chunk does not meet minimum length requirements");
    }


    // acquire token position for external processing, if any
    layer1::Token* token()
    {
        return reinterpret_cast<layer1::Token*>(buffer.data() + 4);
    }


    // 100% untested
    void token(const pipeline::MemoryChunk::readonly_t& full_token)
    {
        token()->copy_from(full_token);
    }

    /*
    void token_complete()
    {
        // NOTE: Just be sure token length is assigned by the time we get here
        size_t pos = 4 + header()->token_length();
        writer.advance_write(pos);

    } */

    // option calls untested
    void option(number_t number)
    {
        flush_token(_state_t::Options);
        optionEncoder.option(writer, number);
    }


    pipeline::MemoryChunk option(number_t number, uint16_t length)
    {
        ASSERT_ERROR(true, length > 0, "Length must be > 0");

        flush_token(_state_t::Options);
        optionEncoder.option(writer, number, length);

        return writer.peek_write(length);
    }


    void option(number_t number, const pipeline::MemoryChunk& chunk)
    {
        flush_token(_state_t::Options);
        optionEncoder.option(writer, number, chunk);
    }


    void payload_marker()
    {
        flush_token(_state_t::Payload);
        writer.write(0xFF);
    }


    pipeline::MemoryChunk payload(size_t preferred_minimum_length = 0)
    {
        if(state != _state_t::Payload)
            payload_marker();

        return writer.peek_write(preferred_minimum_length);
    }

    void payload(const pipeline::MemoryChunk& chunk)
    {
        if(state != _state_t::Payload)
            payload_marker();

        writer.write_experimental(chunk);
    }


    inline void advance(size_t advance_amount) { writer.advance_write(advance_amount); }

    // mark encoder as complete, which in turn will mark outgoing writer
    inline void complete()
    {
        writer.advance_write(0, Root::boundary_message);
    }
};



// This buffers more traditionally, outside the writer
// only buffers header and token
class BufferedBlockingEncoder :
    public BlockingEncoder,
    public BufferedEncoderBase

{
    //typedef CoAP::ParserDeprecated::State state_t;
    //typedef CoAP::ParserDeprecated _state_t;
    typedef BufferedEncoderBase::state_t state_t;
    typedef BufferedEncoderBase::_state_t _state_t;

    Header _header;
    moducom::coap::layer1::Token _token;

    typedef BlockingEncoder base_t;

    // ensure header and token are advanced past
    void flush_token(state_t s)
    {
        // TODO: Get rid of BufferedEncoderBase::state since BlockingEncoder
        // already has a state machine (though it's debug only so be careful)
        if(BufferedEncoderBase::state == _state_t::Header)
        {
            uint8_t token_length = _header.token_length();
            base_t::header(_header);
            if(token_length > 0)
                writer.write(_token.data(), _header.token_length());

            base_t::state(_state_t::TokenDone);
        }

        BufferedEncoderBase::state = s;
    }

public:
    BufferedBlockingEncoder(pipeline::IPipelineWriter& writer) : BlockingEncoder(writer) {}

    Header* header() { return &_header; }

    moducom::coap::layer1::Token* token() { return &_token; }

    /*
    // called even if "no" token.  It should be noted that RFC 7252 says there is *always* a
    // token, even if it is a zero length token...
    void token_complete()
    {
        base_t::header(_header);
        writer.write(_token.data(), _header.token_length());
        base_t::state(_state_t::TokenDone);
    } */

    inline void option(option_number_t number, const pipeline::MemoryChunk& value)
    {
        flush_token(_state_t::Options);
        base_t::option(number, value);
    }

    inline void option(option_number_t number)
    {
        flush_token(_state_t::Options);
        base_t::option(number);
    }

    inline void option(option_number_t number, const char* str)
    {
        flush_token(_state_t::Options);
        base_t::option(number, str);
    }

};


template <typename custom_size_t = size_t>
class ProcessedMemoryChunkBase
{
protected:
    custom_size_t _processed;

public:
    ProcessedMemoryChunkBase(custom_size_t p = 0) : _processed(p) {}

    custom_size_t processed() const { return _processed; }
    void processed(custom_size_t p) { _processed = p; }
};

// length = total buffer size
// processed = "valid" buffer size, size of buffer actually used
class ProcessedMemoryChunk :
    public pipeline::MemoryChunk,
    public ProcessedMemoryChunkBase<>
{
public:
    ProcessedMemoryChunk(const pipeline::MemoryChunk& chunk) : pipeline::MemoryChunk(chunk) {}

};


namespace layer1 {

template <size_t buffer_size, typename custom_size_t = size_t>
class ProcessedMemoryChunk :
    public pipeline::layer1::MemoryChunk<buffer_size>,
    public ProcessedMemoryChunkBase<custom_size_t>
{
public:
};

}


namespace layer2 {

template <size_t buffer_size, typename custom_size_t = size_t>
class ProcessedMemoryChunk :
        public pipeline::layer2::MemoryChunk<buffer_size, custom_size_t>,
        public ProcessedMemoryChunkBase<custom_size_t>
{
public:
};

}


void process_header_request(Header request, Header* response);


// NOT USED just capturing idea that pipeline reader and pipeline writer might actually be 99% the same
template <class TMessage, typename custom_size_t = size_t>
class IPipeline2
{
    typedef uint8_t boundary_t;

public:
    virtual TMessage current() = 0;

    virtual bool next() = 0;

    virtual custom_size_t advance(custom_size_t length, boundary_t boundary) = 0;
};


namespace v2 {
// NOTE:
// Ultimately we will have 3 classes of data streaming/pipelining:
// 1) classic stream-style copy-oriented, augmented by "boundary" capability
// 2) normal, in which case pipeline "writer" will maintain buffer
// 3) buffered, in which case pipeline itself maintains buffer
//
// right now code architecture is a mess and does not reflect or truly support this

// named experimental::v2 because we have so many experimental things already , so this is current
// newest one

struct v2_traits
{
    typedef size_t custom_size_t;
    typedef uint8_t boundary_t;
};

template <class TTraits = v2_traits>
class IStreamReader
{
    typedef TTraits traits_t;
    typedef typename traits_t::custom_size_t size_t;
    typedef typename traits_t::boundary_t boundary_t;

public:
    // number of bytes available to read, up to boundary condition if specified
    virtual size_t available(boundary_t boundary = 0) = 0;

    // reads read_into.length(), available() or boundary-condition-met bytes, whichever arrives
    // first.  return value reflects bytes read
    // TODO: May also need a way to reflect if boundary is hit
    virtual size_t read(const pipeline::MemoryChunk& read_into, boundary_t boundary = 0) = 0;
};


template <class TTraits = v2_traits>
class IPipelineReader : public IPipeline2<pipeline::PipelineMessage, typename TTraits::custom_size_t>
{
public:

};


template <class TTraits = v2_traits>
class IStreamWriter
{
    typedef TTraits traits_t;
    typedef typename traits_t::custom_size_t size_t;
    typedef typename traits_t::boundary_t boundary_t;

public:
    // how many non-blockable bytes we can write
    virtual size_t writeable() = 0;

    // writes write_from.length(), writeable() whichever comes first.  Demarkates
    // the "end" of this write with boundary
    virtual size_t write(const pipeline::MemoryChunk::readonly_t& write_from, boundary_t boundary = 0) = 0;
};

template <class TTraits = v2_traits>
class IPipelineWriter
{
    typedef TTraits traits_t;
    typedef typename traits_t::custom_size_t size_t;
    typedef typename traits_t::boundary_t boundary_t;

public:
    // returns true if we can register any more messages
    virtual bool writeable() = 0;

    // registers a specified pipeline message.  For now, we still utilize
    // PipelineMessage::CopiedStatus::boundary field, but starting to feel like
    // that might be phased out ... ?  at least in this context
    virtual bool write(const pipeline::PipelineMessage& register_message) = 0;
};


template <class TTraits = v2_traits>
class IBufferedPipelineWriter
{
    typedef TTraits traits_t;
    typedef typename traits_t::custom_size_t size_t;
    typedef typename traits_t::boundary_t boundary_t;

public:

    // Acquire present managed buffer
    virtual pipeline::PipelineMessage current() = 0;

    // Move to next managed buffer
    virtual bool next() = 0;

    // mark the current message at the given position with a boundary
    // NOTE: This clashes with current PipelineMessage::CopiedStatus::boundary approach
    virtual bool boundary(size_t position, boundary_t boundary) = 0;
};



}




}}}

#endif //MC_COAP_TEST_EXPERIMENTAL_H
