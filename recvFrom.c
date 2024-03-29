#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define PORT 8081

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    uint8_t buffer[2];
    uint16_t buffer2[10000];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Socket created\n");
    memset(&servaddr, 0, sizeof(servaddr));
   // memset(&client_addr, 0, sizeof(client_addr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("192.168.1.82");
    servaddr.sin_port = htons(PORT);
    /*if (inet_pton(AF_INET, ip_address, &servaddr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }*/
   if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
        perror("connect failed");
        exit(EXIT_FAILURE);
    }
     printf("Connection Ok\n");
    int i = 0;
    int len = sizeof(servaddr);
    while (1) {
        memset(buffer, 0, sizeof(buffer));
        printf("323\n");
        recvfrom(sockfd, (uint8_t *)buffer, 2, MSG_WAITALL, (struct sockaddr*)&servaddr, &len);
        //printf("Data received: %hhn", buffer);
        printf("123\n");
        buffer2[i] = buffer[1] | (buffer[0] << 8);
        printf("%x ", buffer2[i]);
    }

    close(sockfd);
    return 0;
}
