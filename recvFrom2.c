#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8081
#define BUF_SIZE 1024

int main() {
    //printf("x1322423...n");
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUF_SIZE];
    //printf("x12423...n");
    // Создание UDP сокета
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
   // printf("S1231312423...n");
    // Настройка адреса сервера
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    socklen_t addr_len = sizeof(server_addr);
   // printf("S123...n");
    // Привязка сокета к адресу
    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is running...n");
    //int len = 0;
     //printf("hello");
        //printf("hello");
        // Получение данных от клиента
        int len = recvfrom(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *)&server_addr, &addr_len);
        printf("%s", buffer);
        buffer[len] = '0'; // Добавляем символ конца строки

        // Вывод полученных данных
        //printf("Received packet from %s:%d - %sn", inet_ntoa(server_addr.sin_addr), ntohs(server_addr.sin_port), buffer);

    close(sockfd);
    return 0;
}
