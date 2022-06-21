//udp_server.c
//A simple UDP server in C


//import header files
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>


//define a symbolic constant
#define BUFFER_SIZE 1024


//function prototype
void error_handling(char *message);


//declare function main
int main(int args, char *argv[]){

	if(args != 2){

		printf("[!] Usage: %s  <port_number>", argv[0]);
		exit(1);

	}//end if(args != 2)


	//create the socket
	int server_socketfd = socket(AF_INET, SOCK_DGRAM, 0);

	//check if the socket has been created
	if(server_socketfd == -1){

		error_handling("[-] Socket creation failed.");
	
	}//end if(client_socketfd == -1)

	//initialize a struct instance
	struct sockaddr_in server_address;
	//clean the struct instance
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(atoi(argv[1]));

	//now we bind
	int bind_status = bind(server_socketfd, (struct sockaddr*)&server_address, sizeof(server_address));

	//check if the binding has been successful
	if(bind_status == -1){

		error_handling("[-] Binding failed.");
	
	}//if(bind_status == -1)

	//create buffer to receive message in
	char message[BUFFER_SIZE];	 
	struct sockaddr_in client_address;
	socklen_t client_address_size = sizeof(client_address);

	int recvfrom_value = recvfrom(server_socketfd, message, BUFFER_SIZE, 0, (struct sockaddr*)&client_address, &client_address_size);

	if(recvfrom_value == -1){

		error_handling("[-] Receive error");
	
	}//if(recvfrom_status == -1)
	
	printf("[+] Data received: %s\n", message);
	//clean the message buffer
	memset(message, 0, BUFFER_SIZE);
	strcpy(message, "[!] Hello Client");
	
	int sendto_value = sendto(server_socketfd, message, BUFFER_SIZE, 0, (struct sockaddr*)&client_address, sizeof(client_address));
	if(sendto_value == -1){

		error_handling("[-] Send error.");

	}//if(sendto_status == -1)

	printf("[+] Data send: %s\n", message);

}//end main(int args, char *argv[])


void error_handling(char *message){

	fputs(message, stderr);
	fputc('\0', stderr);
	exit(1);

}//end error_handling(char *message)  