//uecho_client.c
//A simple uecho_client in C

//import header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>


//define a symbolic constant
#define BUFFER_SIZE 30


//define a function prototype
void error_handling(char *message);


//declare a function main
int main(int argc, char *argv[]){
	
	if(argc != 3){
	
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	
	}//end if(argc!=3)
	
	//create a socket
	int client_socketfd = socket(PF_INET, SOCK_DGRAM, 0);  

	//check if socket creation has been successsful.
	if(client_socketfd == -1)
		error_handling("[!] socket() error");
	
	//intantiate a sockaddr_in struct
	struct sockaddr_in server_address;
	//now clean the struct instance
	memset(&server_address, 0, sizeof(server_address));
	//now fill up the structure
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr(argv[1]);
	server_address.sin_port = htons(atoi(argv[2]));
	
	char message[BUFFER_SIZE];
	int str_len;

	struct sockaddr_in client_address;
	socklen_t client_address_size = sizeof(client_address);

	while(1){
		
		fputs("Insert message(q to quit): ", stdout);
		fgets(message, sizeof(message), stdin);     
		
		//check if the user wishes to quit
		if(!strcmp(message,"q\n") || !strcmp(message,"Q\n"))	
			break;
		

		sendto(client_socketfd, message, strlen(message), 0, 
					(struct sockaddr*)&server_address, sizeof(server_address));
		
		
		str_len = recvfrom(client_socketfd, message, BUFFER_SIZE, 0, 
					(struct sockaddr*)&client_address, &client_address_size);

		message[str_len]=0;
		printf("Message from server: %s", message);
	
	}//while(1)	
	
	close(client_socketfd);
	
	return 0;

}//main(int argc, char *argv[])


void error_handling(char *message){

	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);

}//error_handling(char *message)