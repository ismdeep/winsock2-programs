/* TCPServer.c */
#include <winsock2.h>
#include <stdio.h>

#define PORT 4433

#pragma comment(lib, "ws2_32.lib")

int main()
{
	/* WSAStartup */
	WSADATA wsaData;
	int ret = 0;
	WSAStartup(MAKEWORD(2,2), &wsaData);

	/* socket */
	SOCKET fd_socket;
	fd_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	bind(fd_socket, (SOCKADDR *)&server_addr, sizeof(SOCKADDR));

	/* listen */
	listen(fd_socket, 10);
	
	/* accept */
	SOCKADDR_IN client_addr;
	SOCKET fd_client;
	fd_client = accept(fd_socket, (SOCKADDR *)&client_addr, NULL);

	/* recv */
	char recv_buff[1024];
	memset(recv_buff, 0, 1024);
	ret = recv(fd_client, recv_buff, 1024, 0);
	printf("Recv: {%s}\n", recv_buff);

	/* send */
	char send_buff[512];
	memset(send_buff, 0, 512);
	strcpy(send_buff, "Hello, I\'m a TCP server.");
	send(fd_client, send_buff, strlen(send_buff), 0);
	printf("Send: {%s}\n", send_buff);

	/* closesocket */
	closesocket(fd_client);
	closesocket(fd_socket);

	/* WSACleanup */
	WSACleanup();

	return 0;
}

