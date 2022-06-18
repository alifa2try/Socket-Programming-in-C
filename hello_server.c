//hello_server.c
//A simple server in C

//To run the server, issue the command: ./hello_server 5667

//import header files
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>


//function prototype
void error_handling(char *message);


int main(int argc, char* argv[]){

	if(argc != 2){

		printf("[!] To run the server: %s  <port>", argv[0]);
		exit(1);
	
	}//if(argc != 2)


	//create a socket
	int server_socketfd = socket(AF_INET, SOCK_STREAM, 0);

	if(server_socketfd == -1){

		error_handling("[-] socket() error");
	
	}//end if(bind_status == -1)

	//bind the socket
	struct sockaddr_in server_address; //create sockaddr_in instance
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(atoi(argv[1]));

	int bind_status = bind(server_socketfd, (struct sockaddr*)&server_address, sizeof(server_address));

	if(bind_status == -1){

		error_handling("[-] bind() error");
	
	}//end if(bind_status == -1) 


	//listen
	int listen_status = listen(server_socketfd, 5);

	if(listen_status == -1){

		error_handling("[-] listen() error");
	
	}//end if(listen_status == -1)


	//accept incoming request for connection
	struct sockaddr_in client_address;
	socklen_t client_address_size = sizeof(client_address);

	int client_socketfd = accept(server_socketfd, (struct sockaddr*)&client_address, &client_address_size);

	if(client_socketfd == -1){

		error_handling("[-] accept() error");
	
	}//end if(client_socketfd == -1)


	//communicate with the client
	char message[] = "Hello World!";
	int write_status = write(client_socketfd, message, sizeof(message));

	if(write_status == -1){

		error_handling("[-] write() error");
	
	}//end if(client_socketfd == -1)

	close(client_socketfd);
	close(server_socketfd);

	return 0;


}//end main(int argc, char* argv[])



//error handling
void error_handling(char *message){

	fputs(message, stderr);
	fputc('\0', stderr);
	exit(1);

}//end error_handling(char *message) 