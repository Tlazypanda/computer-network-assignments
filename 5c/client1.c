#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <stdio.h>
#include <arpa/inet.h> 
#include <unistd.h>
#include "float_bundle.h"

int main()
{
    struct sockaddr_in server_add;
    int socket_fd;
    float buffer;
    uint32_t fi;
    printf("Enter floating number : ");
    scanf("%f", &buffer);
    fi = pack754_32(buffer);

    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
		printf("socket() failed \n");
	}

	server_add.sin_family = AF_INET; 
    server_add.sin_port = htons(8080); 
    server_add.sin_addr.s_addr = INADDR_ANY; 

    int m = sendto(socket_fd, (const uint32_t *) &fi, sizeof(uint32_t), 0, (const struct sockaddr *) &server_add, sizeof(server_add));
    printf("Message sent to server \n");

    close(socket_fd);

}