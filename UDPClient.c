#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "002.h"
#define PORT 8080

void error(char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main() {
    FILE *file_ptr;
    int sockfd, connfd;
    struct sockaddr_in servaddr = {0};
    file_ptr = fopen("002.wav", "rb");
    if (file_ptr == NULL) {
        error("Error opening file");
    }
    fseek(file_ptr, 40, SEEK_SET); // Перейти к 40 байту в файле, где находится информация о количестве отсчетов
    uint32_t dataSize;
    //fread(&dataSize, sizeof(uint32_t), 1, file_ptr); // Прочитать количество байт данных
   // printf("Datasize: %u\n", dataSize);
    int sampleSize = 16; // Размер одного отсчета в битах (здесь предполагается, что это короткий int)
    int sampleCount = dataSize * 8 / sampleSize; // Посчитать количество отсчетов
    //printf("Total samples in the wav file: %d\n", sampleCount);
    //printf("%ld\n", ftell(file_ptr));
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        error("Error creating socket");
    }

    servaddr.sin_family = AF_INET;
    //inet_pton(AF_INET, "192.168.1.82", &servaddr.sin_addr);
    servaddr.sin_addr.s_addr = inet_addr("192.168.1.203"); //203
    servaddr.sin_port = htons(PORT);

    printf("ip:%d\n",servaddr.sin_addr.s_addr);
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
        error("Connection failed");
    }
    int i =0;
    int bytes_read;
    char c;
    //char str[256] = "1233214214";
   // short buffer[5]= {10000,20000,30000,-32000,30500};
   // char* symb = (char *)&buffer[0];
    unsigned char buf[2] = {0};
    //fseek(file_ptr, 44, SEEK_SET); // Skip the header of the wav file (44 bytes)
   // send(sockfd, symb, 10, 0);
    while (_002_raw[i] != 0) {
       // printf("%d ",_002_raw[i]);
        buf[0] = _002_raw[i]; 
        i++;
        send(sockfd, buf, 1, 0);
        sleep(1);
    }

    printf("File sent successfully\n");
    close(sockfd);
    fclose(file_ptr);

    return 0;
}
