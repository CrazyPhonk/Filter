#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    uint8_t buffer[2];
    uint16_t buffer2[10000];
    // Создание UDP сокета
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);
    int i = 0;
    while (1) {
        memset(buffer, 0, sizeof(buffer));
        recvfrom(sockfd, (uint8_t *)buffer, 2, MSG_WAITALL, NULL, NULL);
        printf("Data received: %hhn", buffer);
        buffer2[i] = buffer[1] | (buffer[0] << 8);
        printf("%x ", buffer2[i]);
    }

    close(sockfd);
    return 0;
}
