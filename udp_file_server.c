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
void write_file(int server_socketfd, struct sockaddr_in client_address);


//function main
int main(int args, char *argv[]){

	if(args != 2){

		printf("[-] Usage: %s <port_number>", argv[0]);
		exit(1);

	}//if(args != 2)


	//socket creation
	int server_socketfd = socket(AF_INET, SOCK_DGRAM, 0);

	//check if the socket has been created
	if(server_socketfd == -1){

		perror("[ERROR] Socket creation failed.");
		exit(1);
	
	}//if(server_socketfd == -1)


	//create a sockaddr_in struct
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(atoi(argv[1]));

	int bind_status = bind(server_socketfd, (struct sockaddr*)&server_address, sizeof(server_address));

	if(bind_status == -1){

		perror("[ERROR] binding failed.");
		exit(1);

	}//if(bind_status == -1)

	printf("[STARTING] UDP File server started.");

	struct sockaddr_in client_address;
	write_file(server_socketfd, client_address);
	printf("[SUCCESS] Data transfer completed.\n");
	printf("[CLOSING] Closing the server.\n");
	close(server_socketfd);

	return 0;

}//main(int args, char *argv[])



void write_file(int server_socketfd, struct sockaddr_in client_address){
	
	FILE *fp;
	char *filename = "server.txt";
	fp = fopen(filename, "w");

	socklen_t client_address_size;
	client_address_size = sizeof(client_address);

	char buffer[SIZE];
	
	while(1){

		recvfrom(server_socketfd, buffer, SIZE, 0, (struct sockaddr*)&client_address, &client_address_size);

		if(strcmp(buffer, "END") == 0){

			break;
			return;

		}//if(strcmp(buffer, "END") == 0)
		
		printf("[RECEIVING] Data: %s", buffer);
		bzero(buffer, SIZE);

	}//while(1)

	fclose(fp);
	return;

}//end 