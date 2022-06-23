//tcp_file_server.c
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
void write_file(int client_socketfd);


int main(int args, char *argv[]){

	if(args != 2){

		printf("[!] Usage: %s <port_number>", argv[0]);
		exit(1);
	
	}//if(args != 2)

	//socket creation
	int server_socketfd = socket(AF_INET, SOCK_STREAM, 0);

	//check if the socket creation has been successful
	if(server_socketfd == -1){

		perror("[-] Error in socket.");
		exit(1);

	}//if(server_socketfd == -1)

	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(atoi(argv[1]));
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);

	int bind_status = bind(server_socketfd, (struct sockaddr*)&server_address, sizeof(server_address));

	if(bind_status == -1){

		perror("[-] Error in binding.");
		exit(1);

	}//if(bind_status == -1)

	//listen
	int listen_status = listen(server_socketfd, 10);	

	if(listen_status == -1){

		perror("[-] Error in listening.");
		exit(1);
	
	}//if(listen_status == -1)

	struct sockaddr_in client_address;
	socklen_t client_address_size = sizeof(client_address);

	//accept client socket
	int client_socketfd = accept(server_socketfd, (struct sockaddr*)&client_address, &client_address_size);

	write_file(client_socketfd);
	printf("[+] Data written in the text file\n");
	close(client_socketfd);
	close(server_socketfd);

}//end main()


void write_file(int client_socketfd){

	char buffer[SIZE];
	char *filename = "file.txt";
	FILE *fp;
	fp = fopen(filename, "w");

	if(fp == NULL){

		perror("[-] Error in creating file");
		exit(1);

	}//end if(fp == NULL)

	int recv_status;

	while(1){

		recv_status = recv(client_socketfd, buffer, SIZE, 0);

		if(recv_status <= 0){

			break;
			return;

		}//end if(recv_status <= 0) 
	
	}//while(1) 

	fprintf(fp, "%s", buffer);
	bzero(buffer, SIZE);
	fclose(fp);
}//end write_file(int client_socketfd) 