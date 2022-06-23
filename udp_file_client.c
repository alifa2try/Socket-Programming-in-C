//udp_file_server.c

//import header files
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>


//symbolic constant
#define SIZE 1024


//function prototype
void send_file(FILE *fp, int client_socketfd, struct sockaddr_in server_address);


//function main
int main(int args, char *argv[]){

	if(args != 3){

		printf("[-] Usage: %s <ip_address>  <port_number>", argv[0]);
		exit(1);

	}//if(args != 3)


	//socket creation
	int client_socketfd = socket(AF_INET, SOCK_DGRAM, 0);

	//check if the socket has been created
	if(client_socketfd == -1){

		perror("[ERROR] Socket creation failed.");
		exit(1);
	
	}//if(client_socketfd == -1)


	//create a sockaddr_in struct
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr(argv[1]);
	server_address.sin_port = htons(atoi(argv[2]));

	FILE *fp;
	char *filename = "client.txt";
	fp = fopen(filename, "r");
	
	if(fp == NULL){

		perror("[ERROR] reading the file");
		exit(1);
	
	}//if(fp == NULL)

	send_file(fp, client_socketfd, server_address);

	printf("[SUCCESS] Data transfer complete.\n");
	printf("[CLOSING] Disconnecting from the server.\n");
	close(client_socketfd);

	return 0;

}//main(int args, char *argv[])



void send_file(FILE *fp, int client_socketfd, struct sockaddr_in server_address){

	char buffer[SIZE];

	while(fgets(buffer, SIZE, fp) != NULL){

		printf("[SENDING] Data: %s", buffer);
		int sendto_status = sendto(client_socketfd, buffer, SIZE, 0, (struct sockaddr*)&server_address, sizeof(server_address));

		if(sendto_status == -1){

			perror("[ERROR] Sending data to the server.");
			exit(1);

		}//end if(sendto_status == -1) 

		bzero(buffer, SIZE);

	}//while(fgets(buffer, SIZE, fp) != NULL)

	strcpy(buffer, "END");

	sendto(client_socketfd, buffer, SIZE, 0, (struct sockaddr*)&server_address, sizeof(server_address));

	fclose(fp);

	return;

}//end	