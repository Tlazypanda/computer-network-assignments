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
    struct sockaddr_in server_add, client2_add;  
    int socket_fd;
    uint32_t buffer ;
    float buffer2;

    
    client2_add.sin_family = AF_INET; /* Internet address family */
    client2_add.sin_addr.s_addr = INADDR_ANY; /* Any incoming interface */
    client2_add.sin_port = htons(8085); /* Local port */

    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
		printf("socket() failed \n");
	}

	if (bind(socket_fd, (struct sockaddr *) &client2_add, sizeof(client2_add)) < 0){
          printf("bind() failed \n");
    }
    
    int n, len ;
    printf("Waiting for message .......... \n");
    n = recvfrom(socket_fd, (uint32_t *) &buffer, sizeof(int), MSG_WAITALL, ( struct sockaddr *) &server_add, &len);
    buffer2 = unpack754_32(buffer);
    printf("Message received from server : %f \n", buffer2);

    close(socket_fd);

}