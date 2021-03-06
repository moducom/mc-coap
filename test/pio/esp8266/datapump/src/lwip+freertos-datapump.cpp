#include <exp/datapump.hpp>
#include <platform/lwip/lwip-datapump.h>
#include <lwip/api.hpp>

#include <lwipopts.h>

// FIX: temporarily conflating datapump and ping responder
#include <simple-ping-responder.hpp>

using namespace moducom::coap;

lwip_datapump_t datapump;

extern "C" void coap_daemon(void *)
{
    // extra-cheezy way of waiting for IP address assignment
    //vTaskDelay(10000);
    // Not needed, we actually do have port open so thats a start

    LwipDatapumpHelper ldh;

    printf("CoAP daemon running\n");

    for(;;)
    {
        ldh.loop(datapump);

        simple_ping_responder(ldh, datapump);

        //yield();
    }
}