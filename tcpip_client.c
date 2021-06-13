/**
 * @brief   This program write message via socket to a port within same localhost network.
 * 
 * @author  Murtadha Bazli Tukimat (murtadhabazlitukimat@gmail.com)
 * @date    24th May 2021
*/

#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SRV_IP      "127.0.0.1"
#define SRV_PORT    8080

int main(void)
{
    int sockfd = 0;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket");
        return -1;
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SRV_PORT);

    if(inet_pton(AF_INET, SRV_IP, &serv_addr.sin_addr) <= 0)
    {
        perror("inet_pton");
        return -1;
    }

    if( connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("connect");
        return -1;
    }

    char buff[3] = { 10, 20, 30 };
    write(sockfd, buff, sizeof(buff));

    close(sockfd);
}