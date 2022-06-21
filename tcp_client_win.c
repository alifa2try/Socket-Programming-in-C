//A TCP client on Windows OS
//tcp_client_win.c


//import header files
#include<stdio.h>
#include<stdlib.h>
#include<winsock2.h>


//function prototype
void error_handling(char *message);


int main(int argc, int argv[]){

	WSADATA wsadata;
	SOCKET client_socketfd;
	SOCKADDR_IN server_addr;
	
	char message[100];

	int strlen = 0, idx = 0, read_len = 0;

	if(argc != 2){

		printf("Usage: %s <port>\n", argv[0]);
		exit(1);

	}//end if(argc != 2) 

	if(WSAStartup(MAKEWORD(2,2), &wsadata) != 0)
		error_handling("WSAStartup() error");

	client_socketfd = socket(AF_INET, SOCK_STREAM, 0);

	if(client_socketfd == INVALID_SOCKET)
		error_handling("socket() creation error");

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(INADDR_ANY);
	server_addr.sin_port = htons(atoi(argv[2]));

	
	connection_status = connect(client_socketfd, (SOCK_ADDR*)&server_addr, sizeof(server_addr));

	if(connection_status == SOCKET_ERROR){

		error_handling("connect() error");
	
	}//if(client_socketfd == INVALID_SOCKET)

	while(read_len = recv(client_socketfd, &message[idx++], 1, 0)){

		if(read_len == -1){

			error_handling("read() error");
			break;
		
		}//end if(read_len == -1) 

		strlen += read_len;

	}//while(read_len = recv(client_socketfd, &message[idx++], 1, 0))

	printf("Function read call count: %d\n", strlen);
	closesocket(client_socketfd);
	WSACleanup();
	return 0;
	
}//end main(int argc, int argv[]) 


void error_handling(char *message){

	fputs(message, stderr);
	fputc('\0', stderr);
	exit(1);

}//error_handling(char *message)