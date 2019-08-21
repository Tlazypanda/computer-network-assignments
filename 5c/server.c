#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <stdio.h>
#include <arpa/inet.h> 
#include <errno.h>
#include <unistd.h>
extern int errno ;
#include <math.h>
#include "float_bundle.h"




int main()
{
	int MAX=1;
	uint32_t buffer;
    float buffer2;
	int socket_fd;
	struct sockaddr_in server_add, client_add, client2_add;
    
	if ((socket_fd = socket(PF_INET, SOCK_DGRAM, 0)) < 0){
		printf("socket() failed \n");
	}

	server_add.sin_family = AF_INET; /* Internet address family */
    server_add.sin_addr.s_addr = INADDR_ANY; /* Any incoming interface */
    server_add.sin_port = htons(8080); /* Local port */

    if (bind(socket_fd, (struct sockaddr *) &server_add, sizeof(server_add)) < 0){
          printf("bind() failed \n");
    }

    client2_add.sin_family = AF_INET; 
    client2_add.sin_addr.s_addr = INADDR_ANY; 
    client2_add.sin_port = htons(8085); 

    int len, n, m; 
    printf("Waiting for message .......... \n");
    n = recvfrom(socket_fd, (uint32_t *) &buffer, sizeof(uint32_t), MSG_WAITALL, ( struct sockaddr *) &client_add, &len); 

    buffer2 = unpack754_32(buffer);
    printf("Message received from client 1 : %f \n", buffer2);
    float to_send = (float)pow(buffer2,1.5);
    uint32_t to_send2 = pack754_32(to_send);

    m = sendto(socket_fd, (const uint32_t *) &to_send2, sizeof(uint32_t), 0, (const struct sockaddr *) &client2_add, sizeof(client2_add));
    printf("Message sent to client \n"); 

    close(socket_fd);



}
