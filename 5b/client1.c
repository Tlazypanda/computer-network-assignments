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
    struct sockaddr_in server_add;
    int socket_fd;
    int buffer;
    printf("Enter integer : ");
    scanf("%d", &buffer);
    buffer = htons(buffer);

    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
		printf("socket() failed \n");
	}

	server_add.sin_family = AF_INET; 
    server_add.sin_port = htons(8080); 
    server_add.sin_addr.s_addr = INADDR_ANY; 

    int m = sendto(socket_fd, (const int *) &buffer, sizeof(int), 0, (const struct sockaddr *) &server_add, sizeof(server_add));
    printf("Message sent to server \n");

    close(socket_fd);

}