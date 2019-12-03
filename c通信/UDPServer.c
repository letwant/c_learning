#include <winsock2.h>
#include <stdio.h>
#include <Ws2tcpip.h>
#pragma comment(lib,"ws2_32.lib")

void InitWinsock()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
}

int main(int argc, char* argv[])
{
	SOCKET socketS;

	InitWinsock();
	struct sockaddr_in local;
	struct sockaddr_in from;
	int fromlen = sizeof(from);
	local.sin_family = AF_INET;
	local.sin_port = htons(1234);
	local.sin_addr.s_addr = INADDR_ANY;

	socketS = socket(AF_INET, SOCK_DGRAM, 0);
	bind(socketS, (LPSOCKADDR)&local, sizeof(local));
	while (1)
	{
		char buffer[1024];
		char str[INET_ADDRSTRLEN];
		ZeroMemory(buffer, sizeof(buffer));
		printf("Waiting...\n");
		if (recvfrom(socketS, buffer, sizeof(buffer), 0, (LPSOCKADDR)&from, &fromlen) != SOCKET_ERROR)
		{
			// 将ip地址转换为str地址
			InetPton(AF_INET, "127.0.0.1", &(from.sin_addr));
			InetNtop(AF_INET, &(from.sin_addr), str, INET_ADDRSTRLEN);
			printf("Received message from %s: %s\n", str, buffer);
			sendto(socketS, buffer, sizeof(buffer), 0, (LPSOCKADDR)&from, fromlen);
		}
		Sleep(50);
	}
	closesocket(socketS);

	return 0;
}