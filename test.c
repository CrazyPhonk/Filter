#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUF_SIZE 4096

int main() {
    FILE *file;
    int sockfd;
    struct sockaddr_in serverAddr;
    char buffer[BUF_SIZE];

    // Открываем файл .wav для чтения
    file = fopen("AC⧸DC - Back In Black.wav", "rb");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    // Создаем сокет
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        exit(1);
    }

    // Задаем адрес сервера
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(PORT);

    // Подключаемся к серверу
    if (connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Error connecting to server");
        exit(1);
    }

    // Читаем и отправляем данные из файла по сокету
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, BUF_SIZE, file)) > 0) {
        if (send(sockfd, buffer, bytesRead, 0) < 0) {
            perror("Error sending data");
            exit(1);
        }
    }

    // Закрываем файл и сокет
    fclose(file);
    close(sockfd);

    return 0;
}
