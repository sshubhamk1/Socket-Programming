#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int main(void)
{
	char server_msg[256] = "Hello, From server";	// server response message
	int server_socket = socket(AF_INET, SOCK_STREAM, 0); // creating tcp/ip socket for server

	struct sockaddr_in server_address;	// creating server address
	server_address.sin_family = AF_INET;	
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;

	bind(server_socket,(struct sockaddr *)&server_address, sizeof(server_address)); //binding socket to server address

	listen(server_socket, 5); //making connection limited to 5 clients

	int client_socket = accept(server_socket,NULL,NULL);	//accepting the client request
	send(client_socket,server_msg,sizeof(server_msg),0);	// sending server_msg to client
	printf("Message sent to client\n");		//displaying success to console
	close(server_socket); // closing the server socket
	return 0;	
}