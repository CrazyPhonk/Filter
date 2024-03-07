#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define CLIENT_IP "192.168.1.82"
#define PORT 8888

char buf3 [256];
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

    int server_socket, client_socket, addr_len, recv_len, snd_len;
    struct sockaddr_in server_addr, client_addr;

    // Создание UDP сокета
    if ((server_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));
    // Настройка адреса сервера
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    // Связывание сокета с адресом сервера
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    addr_len = 0;
    printf("Waiting...\n");
    char check;
    check=  buf3[0];
    if(check == buf3[0]) printf("nice\n");
    // Принятие данных от клиента и вывод их на stdout
    int i = 0;
    int flag = 0;
    while(1){
     int buffrx = recvfrom(server_socket, &buf3, sizeof(buf3), 0, (struct sockaddr *)&client_addr,  &addr_len);
    if(buffrx == -1)
    {
      perror("recvfrom");
    }
    if (check != buf3[0]){
        flag ++;
        printf("BUF3 = %s\n", buf3);
    }
    if (flag >0) break;
    }
    while(1){

        snd_len = sendto(server_socket, buffer, sizeof(buffer), 0,  (struct sockaddr *)&client_addr, sizeof(client_addr));
            if (snd_len == -1) {
            perror("Write error");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    close(server_socket);

    return 0;
}
