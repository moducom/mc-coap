#pragma once

#include "decoder/subject.h"
#include "experimental-observer.h"
#include <estd/vector.h>

namespace moducom { namespace  coap {

// Not seeing anything specific in RFC7641 mandating or denying the use of CON or NON
// messaging for observables, thereby implying we don't need to track what flavor
// we are in this context either
// TODO: Use specialization to make an ObservableSession with a 'void' key
template <class TAddr, class TResourceKey = int>
struct ObservableSession
{
    typedef TAddr addr_t;
    typedef TResourceKey key_t;

    TResourceKey key; // indicates which resource in particular this observable session subscribed to

    // increases with each observe notification.  Technically only needs to be 24 bits
    // so if we do need flags, we can make this into a bit field.  Also, as suggested
    // in RFC7641, we might do without a sequence# altogether and instead use a mangled
    // version of system timestamp.  In that case, holding on to sequence# here might
    // be a waste.  What does not seem to be specified at all is how to
    // handle rollover/overflow conditions.
    uint32_t sequence;

    // we are the subject, so addr is address of observer - the one
    // who subscribed to us
    TAddr addr;

    // token is one presented during initial subscription
    layer2::Token token;
};


// A registrar represents ONE subject's list of listeners.  By subject
// we generally mean one subscribable URI path
template <class TCollection,
          class TIncomingContext = AddressContext<
              typename TCollection::value_type::addr_t
              >,
          class TRequestContextTraits = incoming_context_traits<TIncomingContext> >
class ObservableRegistrar
{
    typedef pipeline::MemoryChunk::readonly_t ro_chunk_t;

    // Enumeration shall be of type ObservableSession, or something similar to it
    TCollection registrations;

    typedef typename TCollection::value_type observable_session_t;
    typedef typename TCollection::iterator iterator;

public:
    typedef TIncomingContext request_context_t;
    typedef typename request_context_t::addr_t addr_t;
    typedef observable_session_t key_t;


    void do_register(const layer3::Token& token, const addr_t& addr)
    {
        observable_session_t os;

        os.sequence = 0;
        os.token = token;
        os.addr = addr;

        registrations.push_back(os);
    }

    void do_register(const layer2::Token& token, const addr_t& addr)
    {
        observable_session_t os;

        os.sequence = 0;
        os.token = token;
        os.addr = addr;

        registrations.push_back(os);
    }

    template <bool inline_token>
    void do_register(const IncomingContext<addr_t, inline_token>& context)
    {
        do_register(context.token(), context.address());
    }



    void do_deregister()
    {

    }

    iterator begin()
    {
        return registrations.begin();
    }

    iterator end()
    {
        return registrations.end();
    }


    // When evaluating a registration or deregistration, utilize this context
    class Context
    {
    public:
        // true = is registering
        // false = is deregistering
        const bool is_registering;

        // will be carrying address info
        const request_context_t& incomingContext;

        Context(const request_context_t& incomingContext, bool is_registering) :
            incomingContext(incomingContext),
            is_registering(is_registering)
        {
        }
    };

    // when ObservableOptionObserverBase finds a registration or deregistration,
    // call this
    void on_uri_path(Context& context, const ro_chunk_t& chunk, bool last_chunk) {}

    // when ObservableOptionObserverBase completes a registration or deregistration gather
    // call this
    void on_complete(Context& context)
    {
        observable_session_t test;

        test.token = context.incomingContext.token();
        //test.addr = context.incomingContext.address();

        // ObservableSession equality shall rest on the token value
        if(context.is_registering)
        {
            registrations.push_front(test);
        }
        else
        {
            // TODO: need session equality operator in place
            //registrations.remove(test);
        }
    }
};

namespace layer1 {

template<class TAddr, size_t N,
        class TResourceKey = int,
        class TObservableSession = ObservableSession<TAddr, TResourceKey> >
class ObservableRegistrar :
        public moducom::coap::ObservableRegistrar<
                estd::layer1::vector<TObservableSession, N> >
{
};

}

template <class TRequestContext = ObserverContext>
class ObservableOptionObserverBase : public experimental::MessageObserverBase<TRequestContext>
{
    typedef experimental::MessageObserverBase<TRequestContext> base_t;
    typedef typename base_t::context_t request_context_t;
    typedef typename base_t::context_traits_t request_context_traits;
    typedef typename base_t::context_t::addr_t addr_t;
    typedef ObservableSession<addr_t> observable_session_t;

    typedef typename base_t::option_number_t option_number_t;
    typedef typename base_t::ro_chunk_t ro_chunk_t;

    // FIX: Once LinkedListPool is operational use that for our allocator
    // or at least have it as a default template parameter for ObservableOptionObserverBase itself
    typedef estd::forward_list<
            observable_session_t,
                estd::experimental::ValueNode<
                    observable_session_t,
                    estd::experimental::forward_node_base
                >
            >
            enumeration_t;

    typedef ObservableRegistrar<enumeration_t> registrar_t;

    // specifically leave this uninitialized, on_option must be the one
    // to initialize it
    bool is_registering;

    // FIX: mainly for experimentation at this time, though I expect it
    // will look similar when it settles down
    registrar_t registrar;

public:
    ObservableOptionObserverBase(request_context_t& context) :
        base_t(context)
    {}

    void on_option(option_number_t number, uint16_t len) {}

    void on_option(option_number_t number, const ro_chunk_t& chunk, bool last_chunk);

    void on_complete();
};

}}


#include "observable.hpp"
