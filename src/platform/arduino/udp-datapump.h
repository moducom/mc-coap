#pragma once

#include "exp/datapump.h"
#include "stream-netbuf.h"
#include <Udp.h> // Arduino ethernet(ish) client abstractions

namespace moducom { namespace coap { namespace arduino {

struct PortAndAddress
{
    IPAddress address;
    uint16_t port;
};

typedef moducom::coap::DataPump<moducom::mem::StreamNetbuf, PortAndAddress> udp_datapump_t;

void nonblocking_datapump_loop(UDP& udp, udp_datapump_t& datapump);

}}}