#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define CLIENT_IP "192.168.43.219"
#define PORT 8888

int main() {
     FILE *file;
    file = fopen("AC⧸DC - Back In Black.wav", "rb");

    if (file == NULL) {
        fprintf(stderr, "Ошибка открытия файла\n");
        return 1;
    }
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    printf("File size: %ld\n", file_size);
    //short buffer;
    short *buffer = (short*)malloc(44);
    //printf("123");
    rewind(file);
    fread(&buffer, sizeof(short), 1, file);
    fclose(file);

    int server_socket, client_socket, addr_len, recv_len;
    struct sockaddr_in server_addr, client_addr;

    // Создание UDP сокета
    if ((server_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    client_addr.sin_addr.s_addr = inet_addr(CLIENT_IP);
    client_addr.sin_port = htons(PORT);
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
    int i = 0;
    while(1){
        recv_len = sendto(server_socket, buffer, 1024, 0, client_addr.sin_addr.s_addr, sizeof client_addr);
            if (recv_len == -1) {
            perror("Write error");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    close(server_socket);

    return 0;
}
