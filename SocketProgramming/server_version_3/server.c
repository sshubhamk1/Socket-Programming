#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

void print_client(struct sockaddr_in client_address)
{
	unsigned long address = ntohl(client_address.sin_addr.s_addr);
	unsigned int a = (address & (0xff));
	unsigned int b = (address & (0xff <<  8)) >>  8;
	unsigned int c = (address & (0xff << 16)) >> 16;
	unsigned int d = (address & (0xff << 24)) >> 24;
	printf("Cient address: %u.%u.%u.%u ",d,c,b,a);
	return;
}

int main(void)
{
	char server_msg[256] = "Hello, From server";	// server response message
	char end_msg[256] = "Exiting the server";// server ending message
	char client_request[256];
	int client_request_len;
	int server_socket = socket(AF_INET, SOCK_STREAM, 0); // creating tcp/ip socket for server

	struct sockaddr_in server_address;	// creating server address
	server_address.sin_family = AF_INET;	
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;

	if(bind(server_socket,(struct sockaddr *)&server_address, sizeof(server_address)) < 0) //binding socket to server address
	{
		printf("Could not bind address try later!\n");
	}
	listen(server_socket, 5); //making connection limited to 5 clients
	struct sockaddr_in client_address;
	unsigned int client_address_len;
	int client_socket = accept(server_socket,(struct sockaddr *)&client_address,&client_address_len);	//accepting the client request
	print_client(client_address);
	printf(" and port: %u connected\n",client_address.sin_port);
	send(client_socket,server_msg,sizeof(server_msg),0);
	while(1)
	{
		memset(client_request,0,sizeof(client_request)); // cleaning the buffer
		recv(client_socket,&client_request,sizeof(client_request),0); // receiving request from client
		printf("Message from client: %s\n",client_request);
		if(strcmp(client_request,"exit")==0)
		{
			printf("breaking condition\n");
			break; // terminating the connection
		}
		send(client_socket,server_msg,sizeof(server_msg),0);	// sending server_msg to client
	}
	printf("send this message\n");
	send(client_socket,end_msg,sizeof(end_msg),0);
	close(server_socket); // closing the server socket
	return 0;	
}