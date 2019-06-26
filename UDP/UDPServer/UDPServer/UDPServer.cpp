/* UDPServer.c */
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
	server_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	/* bind */
	bind(fd_socket, (SOCKADDR *)&server_addr, sizeof(SOCKADDR));
	
	/* recvfrom */
	SOCKADDR_IN client;
	int client_len = sizeof(client);
	char buff[1024];
	memset(buff,0x0,1024);
	recvfrom(fd_socket,buff,1024,0,(SOCKADDR *)&client,&client_len);
	printf("Recv: {%s}\n", buff);
	
	/* sendto */
	char send_buff[512];
	memset(send_buff,0x0,512);
	strcpy(send_buff, "Hello, client. I\'m server.");
	sendto(fd_socket,send_buff,strlen(send_buff),0,(SOCKADDR *)&client,client_len);
	printf("Send: {%s}\n", send_buff);
	/* closesocket */
	closesocket(fd_socket);

	/* WSACleanup */
	WSACleanup();

	return 0;
}

