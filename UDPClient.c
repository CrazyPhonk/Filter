#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define PORT 8080

void error(char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main() {
    FILE *file_ptr;
    int sockfd, connfd;
    struct sockaddr_in servaddr = {0};

    file_ptr = fopen("AC⧸DC - Back In Black.wav", "rb");
    if (file_ptr == NULL) {
        error("Error opening file");
    }
   
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        error("Error creating socket");
    }

    servaddr.sin_family = AF_INET;
    //inet_pton(AF_INET, "192.168.1.82", &servaddr.sin_addr);
    servaddr.sin_addr.s_addr = inet_addr("192.168.1.82");
    servaddr.sin_port = htons(PORT);

    printf("ip:%d\n",servaddr.sin_addr.s_addr);
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
        error("Connection failed");
    }

    int bytes_read;
    char buffer[1024];
    while ((bytes_read = fread(buffer, sizeof(buffer), 1, file_ptr)) > 0) {
        send(sockfd, buffer, bytes_read, 0);
    }

    printf("File sent successfully\n");
    close(sockfd);
    fclose(file_ptr);

    return 0;
}
