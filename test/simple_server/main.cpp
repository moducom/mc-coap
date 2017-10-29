#include <iostream>

#include "../../src/coap_transmission.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

// bits adapted from http://www.linuxhowtos.org/data/6/server.c
// and https://www.cs.rutgers.edu/~pxk/417/notes/sockets/udp.html

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

using namespace moducom::coap;

class TestResponder : public CoAP::IResponder
{
public:
    virtual void OnHeader(const CoAP::Header header) OVERRIDE;
    virtual void OnToken(const uint8_t message[], size_t length) OVERRIDE;
    virtual void OnOption(const CoAP::OptionExperimental& option) OVERRIDE;
    virtual void OnPayload(const uint8_t message[], size_t length) OVERRIDE;
};

void TestResponder::OnHeader(const CoAP::Header header) {}

void TestResponder::OnOption(const CoAP::OptionExperimental &option) {}

void TestResponder::OnPayload(const uint8_t *message, size_t length) {}

void TestResponder::OnToken(const uint8_t *message, size_t length) {}

int main()
{
    //moducom::coap::CoAP::Header header;
    experimental::OutgoingResponseHandler out_handler(nullptr);
    experimental::TestResponder responder;
    TestResponder user_responder;
    CoAP::Parser parser;

    responder.add_handle("basic/", &user_responder);

    std::cout << "Hello, World!" << std::endl;

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;

    uint8_t buffer[1024];

    if(sockfd < 0) error("ERROR opening socket");

    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5683);

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

        //if(newsockfd < 1) error("ERROR on accept");

        bzero(buffer, 1024);

        //size_t n = read(newsockfd, buffer, 1024);
        ssize_t n = recvfrom(newsockfd, buffer, sizeof(buffer), 0, (sockaddr*) &cli_addr, &clilen);

        std::cout << "Got packet: " << n << " bytes" << std::endl;

        CoAP::ParseToIResponder parser2(&responder);

        if(n > 0)
            parser2.process(buffer, n);

        //close(newsockfd);
    }

    return 0;
}