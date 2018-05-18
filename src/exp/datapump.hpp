#include "datapump.h"

namespace moducom { namespace coap {

template <class TNetBuf, class TAddr, class TAllocator>
#ifdef FEATURE_MCCOAP_DATAPUMP_INLINE
void DataPump<TNetBuf, TAddr, TAllocator>::transport_in(TNetBuf&& in, const addr_t& addr)
{
    incoming.emplace(std::forward<TNetBuf>(in), addr);
}
#else
void DataPump<TNetBuf, TAddr, TAllocator>::transport_in(TNetBuf& in, const addr_t& addr)
{
    Item item(in, addr);

    incoming.push(item);
}
#endif

}}
