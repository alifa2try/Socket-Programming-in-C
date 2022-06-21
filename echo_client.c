//echo_client.c
//A simple TCP echo_client

//import header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>


//function prototype
void error_handling(char *message);


//symbolic constant
#define BUFFER_SIZE 1024


//function main
int main(int argc, char *argv[]){
	

	if (argc !=3){
		printf("Usage : %s <IP> <port>\n",argv[0]);
		exit(1);
	}
	

	//create a socket creation
	int client_socketfd = socket(AF_INET,SOCK_STREAM, 0);
	
	//confirm that a socket has been created
	if(client_socketfd == -1)
		error_handling("socket() error");
	
	//instantiate a struct instance
	struct sockaddr_in server_address;
	//now tidy up the structure
	memset(&server_address, 0, sizeof(server_address));
	//next popultate the structure
	server_address.sin_family=AF_INET;
	server_address.sin_addr.s_addr=inet_addr(argv[1]);
	server_address.sin_port=htons(atoi(argv[2]));
	
	//connection
	int connect_status = connect(client_socketfd,(struct sockaddr*)&server_address, sizeof(server_address));
	
	if(connect_status == -1)	
		error_handling("[-] Connection() error");
	else
		puts("[+] Connection is established....");
	
	//now we can communicate
	char message[BUFFER_SIZE];
	int str_len;
	while(1)
	{
		
		fputs("Input message (Q to quit): ", stdout);
		fgets(message, BUFFER_SIZE, stdin);

		//check if the user wishes to quit
		if(!strcmp(message,"q\n")||!strcmp(message,"Q\n"))
			break;

		//write a message to the server via our client_socketfd
		write(client_socketfd, message, strlen(message));
		
		//receive the server echo
		str_len = read(client_socketfd, message, BUFFER_SIZE-1);
		message[str_len] = 0;
		printf("Message from the server : %s ",message);
	
	}//while(1)
	
	close(client_socketfd);	
	
	return 0;

}//end main(int argc, char *argv[])


void error_handling(char*message){
	
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);

}//end error_handling(char*message)