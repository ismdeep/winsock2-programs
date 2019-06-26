/* UDPClient.c */
#include <winsock2.h>
#include <stdio.h>

#define PORT 8899

#pragma comment(lib, "ws2_32.lib")

int main()
{
	/* WSAStartup */
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2), &wsaData);

	/* socket */
	SOCKET fd_socket;
	fd_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	SOCKADDR_IN server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	/* sendto */
	int server_len = sizeof(server_addr);
	char send_buff[512];
	memset(send_buff, 0, 512);
	strcpy(send_buff, "Hello, server. I\'m client.");
	sendto(fd_socket, send_buff, strlen(send_buff), 0, (SOCKADDR *)&server_addr, server_len);
	printf("Send: {%s}\n", send_buff);

	/* recvfrom */
	server_len = sizeof(server_addr);
	char buff[1024];
	memset(buff, 0, 1024);
	recvfrom(fd_socket, buff, 1024, 0, (SOCKADDR *)&server_addr, &server_len);
	printf("Recv: {%s}\n", buff);
	
	/* closesocket */
	closesocket(fd_socket);

	/* WSACleanup */
	WSACleanup();

	return 0;
}

