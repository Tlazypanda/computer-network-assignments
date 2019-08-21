#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <stdio.h>
#include <arpa/inet.h> 
#include <unistd.h>

int main()
{
    struct sockaddr_in server_add, client2_add;  
    int socket_fd;
    int buffer ;

    
    client2_add.sin_family = AF_INET; 
    client2_add.sin_addr.s_addr = INADDR_ANY; 
    client2_add.sin_port = htons(8085); 

    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
		printf("socket() failed \n");
	}

	if (bind(socket_fd, (struct sockaddr *) &client2_add, sizeof(client2_add)) < 0){
          printf("bind() failed \n");
    }
    
    int n, len ;
    printf("Waiting for message .......... \n");
    n = recvfrom(socket_fd, (int *) &buffer, sizeof(int), MSG_WAITALL, ( struct sockaddr *) &server_add, &len);
    buffer = ntohs(buffer);
    printf("Message received from server : %d \n", buffer);

    close(socket_fd);

}
