/**
 * @brief   This program read message from client within same localhost network.
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
    int sockfd, connfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    {
        perror("socket");
        return -1;
    }

    int reuse_addr = 1;
    int sc;
    sc = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof(int));
    if(sc < 0)
    {
        perror("setsockopt");
        close(sockfd);
        return -1;
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    if(inet_pton(AF_INET, SRV_IP, &serv_addr.sin_addr.s_addr) <= 0)
    {
        perror("inet_pton");
        close(sockfd);
        return -1;
    }

    serv_addr.sin_port = htons(SRV_PORT);
    if(bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("bind");
        close(sockfd);
        return -1;
    }

    if(listen(sockfd, 10) < 0)
    {
        perror("listen");
        close(sockfd);
        return -1;
    }

    connfd = accept(sockfd, (struct sockaddr*) NULL, NULL);
    if(connfd < 0) {
        perror("accept");
        return -1;
    }

    char buff[3] = {0};
    read(connfd, buff, sizeof(buff));
    printf("from client: %d %d %d\n", buff[0], buff[1], buff[2]);
}