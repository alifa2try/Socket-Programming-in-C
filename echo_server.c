//echo_server.c
// A simple TCP echo server implemented in C

//import header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>


//function prototype
void error_handling(char *message);


//define a symbolic constant
#define BUFFER_SIZE 1024


//function main
int main(int argc, char *argv[]){
	
	if(argc != 2){
		
		printf("Usage : %s <port>\n",argv[0]);
		exit(1);
	
	}//end if(argc != 2)
	
	//create a socket
	int server_socketfd = socket(AF_INET,SOCK_STREAM, 0);
	
	//confirm that the socket is created
	if(server_socketfd == -1)
		error_handling("socket() error");

	//instantiate a sockaddr_in instance
	struct sockaddr_in server_address;
	//tidy up the struct instance just created
	memset(&server_address, 0, sizeof(server_address));
	//now fill in the structure members
	server_address.sin_family=AF_INET;
	server_address.sin_addr.s_addr=htonl(INADDR_ANY);
	server_address.sin_port=htons(atoi(argv[1]));
	
	//now bind the server_address to the server_socketfd	
	int bind_status = bind(server_socketfd,(struct sockaddr*)&server_address, sizeof(server_address)) == -1;
		
	//confirm that the socket is created
	if(bind_status == -1)
		error_handling("bind() error");	

	//next we listen
	int listen_status = listen(server_socketfd, 5);

	//confirm that we are listening
	if(listen_status ==-1)
		error_handling("listen() error");
	
	//instantiate a sockaddr_in struct for client address
	struct sockaddr_in client_address;
	socklen_t client_address_size = sizeof(client_address);
	
	int str_len;
	char message[BUFFER_SIZE];
	for(int i = 0; i < 5; i++){
		
		int client_socketfd = accept(server_socketfd,(struct sockaddr*)&client_address, &client_address_size);
		
		if(client_socketfd == -1)
			error_handling("accept() error");
		else
			printf("connected client %d\n", i+1);
		
		//what if str_len is -1?
		while((str_len = read(client_socketfd, message, BUFFER_SIZE)) != 0)
			write(client_socketfd, message, str_len);
		close(client_socketfd);
	
	}//for(int i = 0; i < 5; i++)

close(server_socketfd);
	
	return 0;

}//end main(int argc, char *argv[]) 


void error_handling(char *message){

	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);

}//error_handling(char*message)