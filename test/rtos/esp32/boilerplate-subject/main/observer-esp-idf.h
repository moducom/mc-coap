#pragma once

// imported from bronze-star

#include <estd/port/identify_platform.h>

// FIX: Not yet pulling in proper estd esp-idf version finder
// so hardwiring to PROJECT_VER
#define PROJECT_VER "1.0.0-alpha001"

#include <exp/events.h>
#include <exp/uripath-repeater.h>   // brings in UriPathMatcher and friends
#if ESTD_IDF_VER >= ESTD_IDF_VER_3_3_0
#include "esp_ota_ops.h"
#endif

#include <coap/header.h>

// FIX: decouple from specific AppContext, only needs to really be wired to:
// 1. UriPathMatcher
// 2. something which can do a make_encoder/reply
#include "context.h"

// for coap version command request

struct VersionObserverBase
{
    static const char *TAG;
};

template <bool inline_token, class TStreambuf>
void build_version_response(
    const moducom::coap::TokenAndHeaderContext<inline_token>& context, 
    embr::coap::experimental::StreambufEncoder<TStreambuf>& encoder)
{
    typedef moducom::coap::Header Header;
    typedef moducom::coap::Option Option;

    build_reply(context, encoder, Header::Code::Content);

    // text/plain
    encoder.option_int(Option::Numbers::ContentFormat, 0);

    encoder.payload();

    auto out = encoder.ostream();

    out << PROJECT_VER;
}


// Expects TContext to be/conform to:
// moducom::coap::IncomingContext
template <int id_path, class TContext>
struct VersionObserver : VersionObserverBase
{
    typedef moducom::coap::Header Header;
    typedef moducom::coap::Option Option;
    typedef moducom::coap::experimental::completed_event completed_event;

    static void on_notify(completed_event, TContext& ctx) 
    {
        ESP_LOGD(TAG, "on_notify(completed_event)");

        // NOTE: Consider making this into a helper method instead of a whole
        // discrete class
        if(ctx.uri_matcher().last_found() == id_path)
        {
            auto encoder = make_encoder(ctx);

            build_version_response(ctx, encoder);

#ifdef OLD_CODE
            //ESP_LOGD(TAG, "replying with version");

            auto encoder = ctx.make_encoder_experimental(Header::Code::Content);

            // text/plain
            encoder.option(Option::Numbers::ContentFormat, 0);

            encoder.payload_marker();

#if ESTD_IDF_VER >= ESTD_IDF_VER_3_3_0
            const esp_app_desc_t* app_desc = esp_ota_get_app_description();

            encoder << estd::layer2::const_string(app_desc->version);
#else
            encoder << estd::layer2::const_string(PROJECT_VER);
#endif

#endif
            ctx.reply(encoder);
        }
    }
};


// EXPERIMENTAL
// Enjoying breaking things out, but things might actually be simpler
// as a helper method instead of this big old class
template <int id_path>
struct StatsObserver
{
    typedef moducom::coap::experimental::completed_event completed_event;

    static void on_notify(const completed_event& e, AppContext& ctx);
};