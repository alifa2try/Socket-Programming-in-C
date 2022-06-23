//tcp_file_client.c
//Second way of creating file sending client server app from idiot developer youtube tutorials

//import header files
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>


//symbolic constant
#define SIZE 1024


//function prototype
void send_file(FILE *fp, int client_socketfd);


int main(int args, char *argv[]){

	if(args != 3){

		printf("[!] Usage: %s <ip_address>  <port_number>", argv[0]);
		exit(1);
	
	}//if(args != 2)

	//socket creation
	int client_socketfd = socket(AF_INET, SOCK_STREAM, 0);

	//check if the socket creation has been successful
	if(client_socketfd == -1){

		perror("[-] Error in socket.");
		exit(1);

	}//if(client_socketfd == -1)

	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(atoi(argv[2]));
	server_address.sin_addr.s_addr = inet_addr(argv[1]);

	int connect_status = connect(client_socketfd, (struct sockaddr*)&server_address, sizeof(server_address));

	if(connect_status == -1){

		perror("[-] Connect error.");
		exit(1);
	
	}//end if(connect_status == -1)

	FILE *fp;
	char *filename = "file1.txt";
	fp = fopen(filename, "r");

	if(fp == NULL){

		perror("[-] Error in reading file");
		exit(1);

	}//if(fp == NULL)

	send_file(fp, client_socketfd);
	printf("[+] File data send successfully.");
	fclose(fp);
	close(client_socketfd);
	printf("[!] Disconnected from the server");
	return 0;

}//end main


void send_file(FILE *fp, int client_socketfd){

	char data[SIZE] = {0};

	while(fgets(data, SIZE, fp) != NULL){

		if(send(client_socketfd, data, sizeof(data), 0) == -1){

			perror("[-] Error in sending data");
			exit(1);

		}//if(send(client_socketfd, data, sizeof(data), 0) == -1)

		bzero(data, SIZE);

	}//while(fgets(data, SIZE, fp) != NULL)

}//send_file(FILE *fp, int client_socketfd)	