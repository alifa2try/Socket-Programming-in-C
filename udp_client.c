//udp_client.c
//A simple UDP server in C


//import header files
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>


//symbolic constant
#define BUFFER_SIZE 1024


//function prototype
void error_handling(char *message);


//declare function main
int main(int args, char *argv[]){

	if(args != 3){

		printf("[!] Usage: %s  <ip_address>  <port_number>", argv[0]);
		exit(1);

	}//end if(args != 3)


	//create the socket
	int client_socketfd = socket(AF_INET, SOCK_DGRAM, 0);

	//check if the socket has been created
	if(client_socketfd == -1){

		error_handling("[-] Socket creation failed.");
	
	}//end if(client_socketfd == -1)

	//initialize a struct instance
	struct sockaddr_in server_address, client_address;
	//clean the struct instance
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr(argv[1]);
	server_address.sin_port = htons(atoi(argv[2]));

	//create buffer to receive message in
	char message[BUFFER_SIZE];	 
	socklen_t client_address_size = sizeof(client_address);
	memset(&message, 0, sizeof(message));
	strcpy(message, "[!] Hi Server!");

	int sendto_value = sendto(client_socketfd, message, BUFFER_SIZE, 0, (struct sockaddr*)&server_address, sizeof(server_address));
	
	if(sendto_value == -1){

		error_handling("[-] Send error.");

	}//if(sendto_status == -1)

	printf("[+] Data send: %s\n", message);

	//clean the message buffer also bzero(message, 1024)
	memset(message, 0, BUFFER_SIZE);
	
	int recvfrom_value = recvfrom(client_socketfd, message, BUFFER_SIZE, 0, (struct sockaddr*)&client_address, &client_address_size);

	if(recvfrom_value == -1){

		error_handling("[-] Receive fails.");
	}

	message[recvfrom_value]=0;
	printf("[+] Data received: %s\n", message);
	

}//end main(int args, char *argv[])


void error_handling(char *message){

	fputs(message, stderr);
	fputc('\0', stderr);
	exit(1);

}//end error_handling(char *message)  