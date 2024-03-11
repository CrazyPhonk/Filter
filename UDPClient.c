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

    file_ptr = fopen("002.wav", "rb");
    if (file_ptr == NULL) {
        error("Error opening file");
    }
   
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
    char buffer[1024]= {0};
    char buf[1] = {0};
    while ((c = fgetc(file_ptr)) != EOF) {
        buffer[i] = c;
        buf[0] = c;
        printf("%d ", buffer[i]);
        i++;
        send(sockfd, buf, 1, 0);
        sleep(1);
    }

    printf("File sent successfully\n");
    close(sockfd);
    fclose(file_ptr);

    return 0;
}
