#pragma once

#include "exp/datapump.h"
#include <platform/lwip/lwip-netbuf.h>
#include <lwip/api.hpp> // for lwip::Netconn usage

// we don't want any of that stdio stuff here, this is LWIP land!
#define MCCOAP_PUTCHAR_SAVED putchar
#undef putchar

namespace moducom { namespace coap {

struct LwipPortAndAddress
{
    ip_addr_t addr;
    uint16_t port;

    LwipPortAndAddress() {}

    LwipPortAndAddress(netbuf* nb)
    {
        addr = *netbuf_fromaddr(nb);
        port = netbuf_fromport(nb);
    }
};

typedef moducom::coap::DataPump<moducom::mem::LwipNetbuf, LwipPortAndAddress> lwip_datapump_t;

extern void nonblocking_datapump_loop(lwip::Netconn netconn, lwip_datapump_t& datapump);
extern void netconn_callback(netconn* conn, netconn_evt evt, uint16_t len);

template <class TDataPump>
class DatapumpHelperBase
{

};

#define COAP_UDP_PORT 5683


class LwipDatapumpHelper
{
    lwip::Netconn conn;

public:
    typedef lwip_datapump_t::netbuf_t netbuf_t;
    typedef lwip_datapump_t::addr_t addr_t;
    typedef lwip_datapump_t datapump_t;

    LwipDatapumpHelper(int port = COAP_UDP_PORT) : 
        conn(NETCONN_UDP, 0, netconn_callback)
    {
        conn.bind(nullptr, port);

        // TODO: improve this by using callbacks/nonblocking functions
        // utilizing technique as described here https://stackoverflow.com/questions/10848851/lwip-rtos-how-to-avoid-netconn-block-the-thread-forever
        // but we are not using accept, so hopefully same approach applies to a direct
        // recv call
        conn.set_recvtimeout(2);
    }

    ~LwipDatapumpHelper()
    {
        conn.del();
    }

    void loop(lwip_datapump_t& datapump)
    {
        nonblocking_datapump_loop(conn, datapump);
    }

    netbuf_t* dequeue(addr_t* addr_out, lwip_datapump_t& datapump)
    {
        return datapump.transport_front(addr_out);
    }

    void pop(lwip_datapump_t& datapump)
    {
        datapump.transport_pop();
    }

    bool enqueue(netbuf_t& netbuf_out, const addr_t& addr, lwip_datapump_t& datapump)
    {
        return datapump.enqueue_out(netbuf_out, addr);
    }

    lwip::Netconn& netconn() { return conn; } 
};


}}
