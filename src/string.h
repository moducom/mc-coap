//
// Created by malachi on 10/20/17.
//

#ifndef SRC_STRING_H
#define SRC_STRING_H

#include "memory.h"
#include <string.h>
#include <stdint.h>

namespace moducom { namespace std {

// replacement for std::string class which instead uses handle-based memory
class string {
    typedef coap::Memory memory_t;

    memory_t::SmartHandle handle;
    // TODO: optimize size out - perhaps smarthandle itself can track it?
    size_t size;

    // TODO: make this smart enough to not allocate memory until someone actually
    // changes the string
    // TODO: Make final decision about +1 for trailing null or not, or make it a
    // traits kinda thing
protected:
    string(const memory_t::SmartHandle& handle, size_t size) :
            handle(handle),
            size(size) {}
public:
    string(const char* src, memory_t& pool = memory_t::default_pool) :
            size(strlen(src)),
            // FIX: somehow size isn't assigned and have to use strlen(src) again
            handle(pool.allocate(src, strlen(src) + 1), pool)
    {
    }

    // TODO: Do also && move operation for C++11
    string(const string& copy_from) :
            handle(copy_from.handle, copy_from.size),
            size(copy_from.size)
    {

    }

    // experimental.  Safer than leaving string locked open and
    // I imagine 95% of the time this is the operation the caller
    // ultimately wants also
    void populate(char* output)
    {
        char* input = handle.lock<char>();

        memcpy(output, input, size);
        output[size] = 0;

        handle.unlock();
    }

    string& operator += (const char* src)
    {
        size_t src_len = strlen(src);
        handle.resize(size + src_len + 1);
        char* dest = handle.lock<char>();
        memcpy(dest + size, src, src_len);
        size += src_len;
        handle.unlock();
        return *this;
    }

    inline string operator +(const char *src) const
    {
        // FIX: Not yet working!
        size_t src_len = strlen(src);
        memory_t::SmartHandle new_handle =
                handle.append_into_new_experimental(src, size, src_len);
        string new_str(new_handle, size + src_len);
        /*
        string new_str(*this);

        size_t src_len = strlen(src);
        handle.resize(size + src_len + 1);
        */

        return new_str;
    }

    inline const char* lock() { return handle.lock<char>(); }
    inline const void unlock() { handle.unlock(); }
};

}}
#endif //SRC_STRING_H
