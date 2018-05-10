#pragma once

namespace moducom { namespace coap { namespace experimental {

// revamped message observer support code

template <class TContext>
struct request_context_traits;

template <class TRequestContext, class TRequestContextTraits = request_context_traits<TRequestContext> >
class RequestContextContainer
{
protected:
    TRequestContext* m_context;

public:
    typedef TRequestContext context_t;
    typedef TRequestContextTraits context_traits_t;

    context_t& context() { return *m_context; }

    const context_t& context() const { return *m_context; }
};

}}}