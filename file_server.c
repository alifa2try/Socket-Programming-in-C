//file_server.c

//import header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>


//define symbolic constant
#define BUFFER_SIZE 30


//function prototype
void error_handling(char *message);


//function main
int main(int argc, char *argv[]){
			 
	if(argc != 2){

		printf("Usage: %s <port>\n", argv[0]);
		exit(1);
	
	}//end if(argc != 2) 
	
	//create a socket
	int server_socketfd = socket(AF_INET, SOCK_STREAM, 0);   
	
	if(server_socketfd == -1){

		error_handling("[-] Socket creation failed.");
	
	}//end if(server_socketfd == -1)

	//instantiate a sockaddr_in struct
	struct sockaddr_in server_address;
	//clean the struct
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(atoi(argv[1]));
	
	//now bind the server_address to the socket
	int bind_status = bind(server_socketfd, (struct sockaddr*)&server_address, sizeof(server_address));
	
	if(bind_status == -1){

		error_handling("[-] Binding failed.");
	
	}//if(bind_status == -1)

	//now we listen
	int listen_status = listen(server_socketfd, 5);

	if(listen_status == -1){

		error_handling("[-] listening failed.");
	
	}//if(listen_status == -1)
	
	//instantiate a sockaddr_in struct
	struct sockaddr_in client_address;
	socklen_t client_address_size;
	client_address_size = sizeof(client_address);    
	//now accept the client socket
	int client_socketfd = accept(server_socketfd, (struct sockaddr*)&client_address, &client_address_size);

	//check if the socket has been accepted
	if(client_socketfd == -1){

		error_handling("[-] Failed to accept client socket");
	
	}//if(client_socketfd == -1)
	
	int read_count;
	char buffer[BUFFER_SIZE];
	FILE *fp;
	fp = fopen("file_server.c", "rb");

	while(1){
		
		read_count = fread((void*)buffer, 1, BUFFER_SIZE, fp);
		
		if(read_count < BUFFER_SIZE){

			write(client_socketfd, buffer, read_count);
			break;
		
		}//if(read_count < BUFFER_SIZE)
			
		write(client_socketfd, buffer, BUFFER_SIZE);
	
	}//while(1)
	
	//half-close socket
	shutdown(client_socketfd, SHUT_WR);	
	read(client_socketfd, buffer, BUFFER_SIZE);
	printf("[!] Message from client: %s \n", buffer);
	
	fclose(fp);
	close(client_socketfd); 
	close(server_socketfd);
	return 0;

}//main(int argc, char *argv[])


void error_handling(char *message){

	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);

}//error_handling(char *message)