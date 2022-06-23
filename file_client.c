//file_client.c

//import header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>


//symbolic constant
#define BUFFER_SIZE 30


//function prototype
void error_handling(char *message);


//function main
int main(int argc, char *argv[]){
		
	if(argc != 3){
	
		printf("Usage: %s <IP> <port>\n", argv[0]);
		exit(1);
	
	}//if(argc != 3)
	

	
	
	//create a socket
	int client_socketfd = socket(AF_INET, SOCK_STREAM, 0); 

	//verify the socket has been created 
	if(client_socketfd == -1){

		error_handling("[-] Socket creation failed.");
	
	}//end if(server_socketfd == -1)
 
	//instantiate a struct
	struct sockaddr_in server_address;
	//clean the struct instance
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr(argv[1]);
	server_address.sin_port = htons(atoi(argv[2]));

	//now we connect to the server
	int connect_status = connect(client_socketfd, (struct sockaddr*)&server_address, sizeof(server_address));
	
	FILE *fp;
	fp = fopen("receive.dat", "wb");
	char buffer[BUFFER_SIZE];
	int read_count;
	
	while((read_count = read(client_socketfd, buffer, BUFFER_SIZE )) != 0)
		fwrite((void*)buffer, 1, read_count, fp);
	
	puts("[+] Received file data.");
	write(client_socketfd, "Thank you", 10);
	fclose(fp);
	close(client_socketfd);
	return 0;

}


void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}