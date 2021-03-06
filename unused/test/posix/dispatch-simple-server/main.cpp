#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "platform.h"
#include "mc/memory-chunk.h"

#include "coap-dispatcher.h"

#include "main.h"

#define COAP_UDP_PORT 5683

void error(const char *msg)
{
    perror(msg);
    exit(1);
}


int main()
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;

    uint8_t buffer[1024];

    if(sockfd < 0) error("ERROR opening socket");

    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(COAP_UDP_PORT);

    if (bind(sockfd, (sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0)
        error("ERROR on binding");

    // listen only for TCP it seems
    //listen(sockfd, 5);

    for(;;)
    {
        // accept only for TCP it seems
        //int newsockfd = accept(sockfd, (sockaddr *) &cli_addr, &clilen);
        int newsockfd = sockfd;

        // should work, but keeping commented until proper tests are conducted
        /*
        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = 100000;
        if (setsockopt(newsockfd, SOL_SOCKET, SO_RCVTIMEO,&tv,sizeof(tv)) < 0) {
            error("Error");
        } */

        //if(newsockfd < 1) error("ERROR on accept");

        bzero(buffer, 1024);

        std::cout << "Waiting for packet" << std::endl;

        //size_t n = read(newsockfd, buffer, 1024);
        ssize_t n = recvfrom(newsockfd, buffer, sizeof(buffer), 0, (sockaddr*) &cli_addr, &clilen);

        std::cout << "Got packet: " << n << " bytes" << std::endl;

        if(n == 0)
            continue;

        moducom::pipeline::layer3::MemoryChunk<256> outbuf;
        size_t send_bytes;

        if(n > 0)
        {
            moducom::pipeline::MemoryChunk inbuf(buffer, n);
            send_bytes = service_coap_in(cli_addr, inbuf, outbuf);
        }
        else
        {
            // NOTE: expected this is where timeout code will live
            // NOTE: timeout-ish code very likely will result in an occasional lost packet when
            //  we aren't listening.  Rather than the complexity of threads, we will live with
            //  this imperfection since it should be a very small sliver of time in which we aren't
            //  listening
            send_bytes = service_coap_out(&cli_addr, outbuf);

            // do this rather than spamming cout with no response created warnings
            if(send_bytes == 0) continue;
        }

        if(send_bytes == 0)
        {
            std::cout << "No response created" << std::endl;
        }
        else
        {
            std::cout << "Responding with " << send_bytes << " bytes" << std::endl;

            sendto(newsockfd, outbuf.data(), send_bytes, 0, (sockaddr*) &cli_addr, clilen);
        }
    }

    // TODO: We never reach here right now, but might someday
    close(sockfd);

    return 0;
}
