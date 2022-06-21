//uecho_server.c
//A simple UDP echo server

//import header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

//symbolic constant
#define BUFFER_SIZE 30


//function prototype
void error_handling(char *message);


//function main
int main(int argc, char *argv[]){
	
	if(argc != 2){
	
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	
	}//end if(argc!=2)

	//socket creation
	int server_socketfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	//verify that socket has been created
	if(server_socketfd == -1)
		error_handling("[-] UDP socket creation error");

	//instantiate a sockaddr_in instance for binding
	struct sockaddr_in server_address;
	//clean the struct instance of any remnant data
	memset(&server_address, 0, sizeof(server_address));
	//now fill the struct members
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(atoi(argv[1]));
	
	//bind now
	int bind_status = bind(server_socketfd, (struct sockaddr*)&server_address, sizeof(server_address));
		
	if(bind_status == -1)	
		error_handling("[-] bind() error");

	char message[BUFFER_SIZE];
	int str_len;
	struct sockaddr_in client_address;
	socklen_t client_address_size = sizeof(client_address);
	
	while(1){
		
		int str_len = recvfrom(server_socketfd, message, BUFFER_SIZE, 0, 
								(struct sockaddr*)&client_address, &client_address_size);
		sendto(server_socketfd, message, str_len, 0, 
								(struct sockaddr*)&client_address, client_address_size);
	}//end while(1) 	
	
	close(server_socketfd);
	
	return 0;

}//main(int argc, char *argv[])


void error_handling(char *message){

	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);

}//end error_handling(char *message)
