//
// Created by malachi on 10/29/17.
//

#include "coap_daemon.h"

namespace moducom { namespace coap {


size_t PassiveDaemon::write(const uint8_t* data, size_t length)
{
    incoming_parser.process(data, length);
}



size_t PassiveDaemon::read(uint8_t* data, size_t length)
{

}


void Daemon::process_iterative()
{
    if(stream_packet)
    {
        if(stream_packet->read_packet())
        {

        }
    }
}


void PipelineDaemon::process_iterate()
{
    MemoryChunk chunk = incoming.read();

    incoming_parser.process(chunk.data, chunk.length);

    outgoing.write(outgoing_generator.get_buffer(), outgoing_generator.get_pos());
}

}}