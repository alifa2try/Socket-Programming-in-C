//tcp_server.c
//A simple tcp server implementation in C


//import header files
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>


//function prototype
void error_handling(char *message);


//function main
int main(int argc, char *argv[]){

	if(argc != 2){

		printf("[!] Usage %s <port>", argv[0]);
		exit(1);
	
	}//end if(argc != 2)

	//socket creation
	int server_socketfd = socket(AF_INET, SOCK_STREAM, 0);

	if(server_socketfd == -1)
		error_handling("socket() error");

	//socket binding to port and IP address
	//instantiate sockaddr_in object
	struct sockaddr_in server_address;
	//now clear the structure object of any remnant data
	memset(&server_address, 0, sizeof(server_address));
	//now populate the structure members
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(atoi(argv[1]));
	int bind_status = bind(server_socketfd, (struct sockaddr*)&server_address, sizeof(server_address));

	//check if binding has been successfull
	if(bind_status == -1){

		error_handling("bind() error");
	
	}//end if(bind_status == -1)
	
	//next we listen 
	int listen_status = listen(server_socketfd, 5);

	//check if listening has been successful
	if(listen_status == -1){

		error_handling("listen() error");
	
	}//if(listen_status == -1)

	//next create a structure for client socket address
	struct sockaddr_in client_address;

	//we need size of client address
	socklen_t client_address_size = sizeof(client_address);
	
	//now accept connection request from a potential client
	int client_socketfd = accept(server_socketfd, (struct sockaddr*)&client_address, &client_address_size);

	//check if accept has been successful
	if(client_socketfd == -1){

		error_handling("accept() error");
	
	}//end if(accept_status == -1)

	//now the message we wanna send
	char message[] = "Assalam Alaiki World!";

	//finally we send the message
	//size_t write (int fd, void* buf, size_t cnt); 
	int write_status = write(client_socketfd, message, sizeof(message));

	if(write_status == -1){

		error_handling("[-] Error in writing to socket!");

	}//end if(write_status == -1) 

	close(client_socketfd);
	close(server_socketfd); 

	return 0;

}//end main(int argc, char *argv[])


//function to notify us of error
void error_handling(char *message){

	fputs(message, stderr);
	fputc('\0', stderr);
	exit(1);

}//end error_handling(char *message[]) 