/* TCPClient.c */
#include <winsock2.h>
#include <stdio.h>

#define PORT 4433

#pragma comment(lib, "ws2_32.lib")

int main()
{
	/* WSAStartup */
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2), &wsaData);

	/* socket */
	SOCKET fd_socket;
	fd_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	/* connect */
	SOCKADDR_IN server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	connect(fd_socket, (SOCKADDR *)&server_addr, sizeof(SOCKADDR));

	/* send */
	char send_buff[512];
	memset(send_buff, 0, 512);
	strcpy(send_buff, "Hello, I\'m a TCP client.");
	send(fd_socket, send_buff, strlen(send_buff), 0);
	printf("Send: {%s}\n", send_buff);

	/* recv */
	char recv_buff[512];
	memset(recv_buff, 0, 512);
	recv(fd_socket, recv_buff, 512, 0);
	printf("Recv: {%s}\n", recv_buff);

	/* closesocket */
	closesocket(fd_socket);
	
	/* WSACleanup */
	WSACleanup();

	return 0;
}

