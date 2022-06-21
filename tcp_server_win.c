//A TCP Server on Windows OS
//tcp_server_win.c


//import header files
#include<stdio.h>
#include<stdlib.h>
#include<winsock2.h>


//function prototype
void error_handling(char *message);


int main(int argc, char *argv[]){

	WSADATA wsadata;
	SOCKET server_socketfd, client_socketfd;
	SOCKADDR_IN server_addr, client_addr;
	int size_client_address;
	char message[] = "Assalam Alaiki World!";

	if(argc != 2){

		printf("Usage: %s <port>\n", argv[0]);
		exit(1);

	}//end if(argc != 2) 

	if(WSAStartup(MAKEWORD(2,2), &wsadata) != 0)
		error_handling("WSAStartup() error");

	server_socketfd = socket(AF_INET, SOCK_STREAM, 0);

	if(server_socketfd == INVALID_SOCKET)
		error_handling("socket() creation error");

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(atoi(argv[1]));

	if(bind(server_socketfd, (SOCKADDR *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR);
		error_handling("bind() error");

	if(listen(server_socketfd, 5) == SOCKET_ERROR);
		error_handling("listen() error");

	size_client_address = sizeof(client_addr);

	client_socketfd = accept(server_socketfd, (SOCKADDR*)&client_addr, &size_client_address);

	if(client_socketfd == INVALID_SOCKET){

		error_handling("accept() error");
	
	}//if(client_socketfd == INVALID_SOCKET)

	send(client_socketfd, message, sizeof(message), 0);
	closesocket(client_socketfd);
	closesocket(server_socketfd);
	WSACleanup();

	return 0;
	
}//end main(int argc, int argv[]) 


void error_handling(char *message){

	fputs(message, stderr);
	fputc('\0', stderr);
	exit(1);

}//error_handling(char *message)