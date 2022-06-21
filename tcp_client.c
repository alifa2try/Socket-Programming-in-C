//tcp_client.c
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

	if(argc != 3){

		printf("[!] Usage %s <ip_address>  <port>", argv[0]);
		exit(1);
	
	}//end if(argc != 3)

	//socket creation
	int client_socketfd = socket(AF_INET, SOCK_STREAM, 0);

	if(client_socketfd == -1)
		error_handling("socket() error");

	
	//instantiate sockaddr_in object
	struct sockaddr_in server_address;

	//now we clean the structure of any remnant data
	memset(&server_address, 0, sizeof(server_address));
	//now we populate the structure members
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr(argv[1]);
	server_address.sin_port = htons(atoi(argv[2]));

	//now connect to the server
	int connect_status = connect(client_socketfd, (struct sockaddr*)&server_address, sizeof(server_address));

	if(connect_status == -1){

		error_handling("[-] Error connecting to the server!");
	
	}//end if(connect_status == -1)

	//now we communicate
	char message[30];
	int str_len = 0;
	int index = 0;
	int read_len = 0;

	//https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write/
	//size_t read (int fd, void* buf, size_t cnt);
	while(read_len = read(client_socketfd, &message[index++], 1)){

		if(read_len == -1){

			error_handling("[-] Read error");
			break;

		}//end if(read_len == -1)

		str_len += read_len;		 

	}//while(read_len = read(client_socketfd, &message[idx++], 1))

	printf("[+] Message from server: %s \n", message); 
	printf("[+] Function read call count: %d \n", str_len);
	close(client_socketfd); 

	return 0;

}//end main(int argc, char *argv[]) 	


//
void error_handling(char *message){

	fputs(message, stderr);
	fputc('\0', stderr);
	exit(1);

}//end error_handling(char *message) 