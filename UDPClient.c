#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "002.1.h"
#define PORT 8080

void error(char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main() {

/*
    FILE *file_ptr;
    int sockfd, connfd;
    struct sockaddr_in servaddr = {0};
    file_ptr = fopen("002.wav", "rb");
    if (file_ptr == NULL) {
        error("Error opening file");
    }
    fseek(file_ptr, 40, SEEK_SET); // Перейти к 40 байту в файле, где находится информация о количестве отсчетов
    uint32_t dataSize;*/
    //fread(&dataSize, sizeof(uint32_t), 1, file_ptr); // Прочитать количество байт данных
   // printf("Datasize: %u\n", dataSize);
    //int sampleSize = 16; // Размер одного отсчета в битах (здесь предполагается, что это короткий int)
    //int sampleCount = dataSize * 8 / sampleSize; // Посчитать количество отсчетов
    //printf("Total samples in the wav file: %d\n", sampleCount);
    //printf("%ld\n", ftell(file_ptr));
	struct sockaddr_in servaddr = {0};
   int  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        error("Error creating socket");
    }

    servaddr.sin_family = AF_INET;
    //inet_pton(AF_INET, "192.168.1.82", &servaddr.sin_addr);
    servaddr.sin_addr.s_addr = inet_addr("192.168.1.82"); //203
    servaddr.sin_port = htons(PORT);

    printf("ip:%d\n",servaddr.sin_addr.s_addr);
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
        error("Connection failed");
    }
    uint8_t buf[40] = {0};
	int i = 0, l = 0;
	for(int j = 0 ; j < 40; j++){
	buf[j] = _002_raw[j];
	i++;
	}
	send(sockfd, buf, 40, 0);
    while (_002_raw[l] != 0) {
       // printf("%d ",_002_raw[
	for(int t = 0; t < 40; t++){
        buf[t] = buf[t+1];
	    }
	    buf[39] = _002_raw[i+1];
	    i++;
        send(sockfd, buf, 40, 0);
	    l++;
        usleep(800000);
    }
    printf("File sent successfully\n");
    close(sockfd);
    return 0;
}
