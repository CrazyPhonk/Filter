#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8081
#define BUF_SIZE 1024
int main() {
    int sockfd;
    uint8_t buffer[2];
    uint16_t buffer2[10000];
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[BUF_SIZE];
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&client_addr, 0, sizeof(client_addr));

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
    int i = 0;
    int len = sizeof(servaddr);
    while (1) {
        // Получение данных от клиента
        int len = recvfrom(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *)&client_addr, &addr_len);
        buffer[len] = '0'; // Добавляем символ конца строки

        // Вывод полученных данных
        printf("Received packet from %s:%d - %sn", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buffer);
    }

    close(sockfd);
    return 0;
}
