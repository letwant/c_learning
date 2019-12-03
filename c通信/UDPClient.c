#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")

void InitWinsock()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
}

int main(int argc, char* argv[])
{
	SOCKET socketC;

	InitWinsock();
	struct sockaddr_in serverInfo;
	int len = sizeof(serverInfo);
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_port = htons(1234);
	// 通过InetPton函数将字符串转换为ip地址
	InetPton(AF_INET, "127.0.0.1", &serverInfo.sin_addr.s_addr);

	socketC = socket(AF_INET, SOCK_DGRAM, 0);
	while (1)
	{
		char buffer[1024];
		ZeroMemory(buffer, sizeof(buffer));
		printf("Please input your message: ");
		scanf_s("%s", buffer, 1024);
		if (strcmp(buffer, "exit") == 0)
			break;
		if (sendto(socketC, buffer, sizeof(buffer), 0, (SOCKADDR*)&serverInfo, len) != SOCKET_ERROR)
		{
			if (recvfrom(socketC, buffer, sizeof(buffer), 0, (SOCKADDR*)&serverInfo, &len) != SOCKET_ERROR)
			{
				printf("Receive response from server: %s\n", buffer);
			}
		}
	}
	closesocket(socketC);

	return 0;
}