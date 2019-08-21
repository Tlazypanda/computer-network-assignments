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
int main()
{
	int MAX=1;
	int buffer;
	int socket_fd;
	struct sockaddr_in server_add, client_add, client2_add;
    
	if ((socket_fd = socket(PF_INET, SOCK_DGRAM, 0)) < 0){
		printf("socket() failed \n");
	}

	server_add.sin_family = AF_INET; 
    server_add.sin_addr.s_addr = INADDR_ANY; 
    server_add.sin_port = htons(8080); 

    if (bind(socket_fd, (struct sockaddr *) &server_add, sizeof(server_add)) < 0){
          printf("bind() failed \n");
    }

    client2_add.sin_family = AF_INET; 
    client2_add.sin_addr.s_addr = INADDR_ANY; 
    client2_add.sin_port = htons(8085); 

    int len, n, m; 
    printf("Waiting for message .......... \n");
    n = recvfrom(socket_fd, (int *) &buffer, sizeof(int), MSG_WAITALL, ( struct sockaddr *) &client_add, &len); 

    buffer = ntohs(buffer);
    printf("Message received from client 1 : %d \n", buffer);
    int to_send = (buffer-1);
    to_send = htons(to_send);

    m = sendto(socket_fd, (const int *) &to_send, sizeof(int), 0, (const struct sockaddr *) &client2_add, sizeof(client2_add));
    printf("Message sent to client \n"); 

    close(socket_fd);



}
