#include <iostream>

#include "sys/socket.h"
#include "sys/types.h"
#include "netinet/in.h"
#include "string.h"
#include "arpa/inet.h"
#include <unistd.h>

#include <stdlib.h>
#include <errno.h>
#include "stdio.h"


#define IPADDR "93.184.216.34" // example.com

int main() {
    int CreateSocket = 0, n = 0;
    char data[1024];
    const char* send_payload = 
        "GET / HTTP/1.0\n"
        "Host: example.com\n" "\n"; // has to end with double newline

    struct sockaddr_in ipOfServer;
    memset(data, '0' ,sizeof(data));
 
    if((CreateSocket = socket(AF_INET, SOCK_STREAM, 0))< 0)
    {
        printf("Socket not created \n");
        return 1;
    }
    
    ipOfServer.sin_family = AF_INET;
    ipOfServer.sin_port = htons(80);
    ipOfServer.sin_addr.s_addr = inet_addr(IPADDR);
 
    std::cout << "Connecting" << std::endl;
    if(connect(CreateSocket, (struct sockaddr *)& ipOfServer, sizeof(ipOfServer))<0)
    {
        printf("Connection failed due to port and ip problems\n");
        return 1;
    }

    std::cout << "Sending data..." << std::endl;
    std::cout << send_payload << "%%%%%%"<< std::endl;
    write(CreateSocket, send_payload, strlen(send_payload));

    std::cout << "Waiting for data..." << std::endl;
    while((n = read(CreateSocket, data, sizeof(data)-1)) > 0)
    {
        data[n] = 0;
        if(fputs(data, stdout) == EOF)
        {
            printf("\nStandard output error");
        }
 
        printf("\n");
    }
 
    if( n < 0)
    {
        printf("Standard input error \n");
    }
 
    return 0;
}
