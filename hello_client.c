//hello_client.c
//A simple server in C

//To run the client, issue the command: ./hello_client ip_address port_number

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

	if(argc != 3){

		printf("[!] To run the client: %s  <ip_address> <port>", argv[0]);
		exit(1);
	
	}//if(argc != 2)


	//create a socket
	int client_socketfd = socket(AF_INET, SOCK_STREAM, 0);

	if(client_socketfd == -1){

		error_handling("[-] socket() error");
	
	}//end if(bind_status == -1)

	//bind the socket
	struct sockaddr_in client_address; //create sockaddr_in instance
	memset(&client_address, 0, sizeof(client_address));
	client_address.sin_family = AF_INET;
	client_address.sin_addr.s_addr = inet_addr(argv[1]);
	client_address.sin_port = htons(atoi(argv[2]));


	//connect to the server

	int connection_status = connect(client_socketfd, (struct sockaddr*)&client_address, sizeof(client_address));

	if(connection_status == -1){

		error_handling("[-] connect() error");
	
	}//end if(connection_status == -1)


	//communicate with the server
	char message[50];
	int read_status = read(client_socketfd, message, sizeof(message) - 1);

	if(read_status == -1){

		error_handling("[-] read() error");
	
	}//end if(read_status == -1)

	printf("[!] Message from the server: %s", message);

	close(client_socketfd);

	return 0;


}//end main(int argc, char* argv[])



//error handling
void error_handling(char *message){

	fputs(message, stderr);
	fputc('\0', stderr);
	exit(1);

}//end error_handling(char *message) 