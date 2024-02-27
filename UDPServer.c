#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8888
#define BUF_SIZE 1024

int main() {
     FILE *file;
    
    char buffer2[BUF_SIZE];
    file = fopen("Scorpions - Wind Of Change.mp3", "rb");

    if (file == NULL) {
        fprintf(stderr, "Ошибка открытия файла\n");
        return 1;
    }
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    char buffer[file_size];
    printf("File size: %ld\n", file_size);
    rewind(file);
    fread(buffer, 1, file_size, file);
    fclose(file);

    int server_socket, client_socket, addr_len, recv_len;
    struct sockaddr_in server_addr, client_addr;

    // Создание UDP сокета
    if ((server_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Настройка адреса сервера
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Связывание сокета с адресом сервера
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    addr_len = sizeof(client_addr);
    printf("Waiting...\n");
    // Принятие данных от клиента и вывод их на stdout
    while (1) {
        recv_len = read(server_socket, buffer2, sizeof(buffer2));
        int flag = 1;
        if (recv_len == -1) {
            perror("Receive error");
            exit(EXIT_FAILURE);
        }
        else if (recv_len == 0){
            break;
        }
        
        printf("Received message from client: %s\n", buffer);
        
    }
        recv_len = write(server_socket, buffer, sizeof(buffer));
            if (recv_len == -1) {
            perror("Write error");
            exit(EXIT_FAILURE);
        }

    close(server_socket);

    return 0;
}
