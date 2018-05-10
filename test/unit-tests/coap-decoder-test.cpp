#include <catch.hpp>

#include "coap-decoder.h"
#include "test-data.h"
//#include "../mc/pipeline.h"

using namespace moducom::coap;
using namespace moducom::pipeline;

TEST_CASE("CoAP decoder tests", "[coap-decoder]")
{
    //layer3::MemoryChunk<1024> buffer_in;
    //buffer_in.memcpy(buffer_16bit_delta, sizeof(buffer_16bit_delta));

    MemoryChunk::readonly_t buffer_in(buffer_16bit_delta);


    layer3::SimpleBufferedPipeline net_in(buffer_in);

    SECTION("Basic test 1")
    {
        OptionDecoder decoder;
        OptionDecoder::OptionExperimental option;

        // pretty much ready to TRY testing, just need to load in appropriate data into buffer_in
        //decoder.process_iterate(net_in, &option);
    }
    SECTION("Payload only test")
    {
        Decoder decoder;
        MemoryChunk::readonly_t chunk(buffer_payload_only);
        Decoder::Context context(chunk, true);

        REQUIRE(decoder.process_iterate(context) == false);
        REQUIRE(decoder.state() == Decoder::Header);
        REQUIRE(decoder.process_iterate(context) == false);
        REQUIRE(decoder.state() == Decoder::HeaderDone);
        REQUIRE(decoder.process_iterate(context) == false);
        REQUIRE(decoder.state() == Decoder::OptionsStart);
        REQUIRE(decoder.process_iterate(context) == false);
        // FIX: Really shouldn't have an Options stage with an overall
        // decoder if no options present.  This may be a case where a little
        // code overlap is desired - just because OptionsDecoder *can* detect
        // payload marker doesn't need we *should* utilize it, though reuse
        // dictates we must consider it
        REQUIRE(decoder.state() == Decoder::OptionsDone);
        // FIX: in any case, we shouldn't be done with the buffer at this point,
        // so failing unit test here is a bug
        REQUIRE(decoder.process_iterate(context) == false);
        REQUIRE(decoder.state() == Decoder::Payload);
    }
    SECTION("16 bit delta test")
    {
        Decoder decoder;
        MemoryChunk::readonly_t chunk(buffer_16bit_delta);
        Decoder::Context context(chunk, true);

        REQUIRE(decoder.process_iterate(context) == false);
        REQUIRE(decoder.state() == Decoder::Header);
        REQUIRE(decoder.process_iterate(context) == false);
        REQUIRE(decoder.state() == Decoder::HeaderDone);
        REQUIRE(decoder.process_iterate(context) == false);
        REQUIRE(decoder.state() == Decoder::OptionsStart);
        // kicks off option decoding itself, first stops after
        // length is processed
        REQUIRE(decoder.process_iterate(context) == false);
        REQUIRE(decoder.state() == Decoder::Options);
        REQUIRE(decoder.option_decoder().state() == OptionDecoder::OptionLengthDone);
        REQUIRE(decoder.option_length() == 1);
        REQUIRE(decoder.process_iterate(context) == false);
        // Would really prefer OptionDeltaDone or OptionLengthAndDeltaDone were exposed here
        REQUIRE(decoder.option_decoder().state() == OptionDecoder::ValueStart);
        REQUIRE(decoder.option_number() == 270);
        REQUIRE(decoder.option_decoder().option_delta() == 270);
        REQUIRE(decoder.process_iterate(context) == false);
        REQUIRE(decoder.state() == Decoder::Options);
        REQUIRE(decoder.option_decoder().state() == OptionDecoder::OptionValueDone);
        REQUIRE(decoder.process_iterate(context) == false);
        REQUIRE(decoder.state() == Decoder::Options);
        REQUIRE(decoder.option_decoder().state() == OptionDecoder::OptionDeltaAndLengthDone);
        REQUIRE(decoder.option_length() == 2);
        REQUIRE(decoder.option_number() == 271);
        REQUIRE(decoder.option_decoder().option_delta() == 1);
        REQUIRE(decoder.process_iterate(context) == false);
        REQUIRE(decoder.state() == Decoder::Options);
        REQUIRE(decoder.option_decoder().state() == OptionDecoder::ValueStart);
        REQUIRE(decoder.process_iterate(context) == false);
        REQUIRE(decoder.state() == Decoder::Options);
        REQUIRE(decoder.option_decoder().state() == OptionDecoder::OptionValueDone);
        REQUIRE(decoder.process_iterate(context) == false);
        REQUIRE(decoder.state() == Decoder::OptionsDone);
    }
}