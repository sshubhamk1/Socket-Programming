#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int main(void)
{
	int client_socket = socket(AF_INET, SOCK_STREAM, 0); //creating client socket

	struct sockaddr_in server_address;	//creating structure for server address
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;

	if(connect(client_socket,(struct sockaddr *)&server_address,sizeof(server_address))<0)	//establishing connection between client and server
	{
		printf("Something went wrong while connecting to server!\n");
		close(client_socket);
		return -3;
	}

	char server_response[256];	//creating buffer for receiving data from server
	char client_request[256];	// creating buffer for sending request from the client
	while(1)
	{
		printf("Enter command: ");
		scanf("%s",client_request);
		send(client_socket,&client_request,sizeof(char)*strlen(client_request),0); // sending command from the client
		memset(server_response,0,sizeof(server_response)); // cleaning the buffer
		recv(client_socket,&server_response,sizeof(server_response),0);	//data receiving from the server
		printf("%s\n",server_response);	//printing data to console
		if(strcmp(client_request,"exit")==0)break; // termnating condition for the client
	}
	close(client_socket);	//closing the socket
	return 0;
}