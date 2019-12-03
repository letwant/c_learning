
#include <winsock2.h>
#include <windows.h>
#pragma comment(lib,"ws2_32.lib")
#include <STDIO.H>
int main(int argc, char* argv[])
{
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	if (WSAStartup(sockVersion, &data) != 0)
	{
		return 0;
	}

	SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sclient == INVALID_SOCKET)
	{
		printf("invalid socket !");
		return 0;
	}

	struct sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(8888);
	serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	if (connect(sclient, (struct sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
	{
		printf("connect error !");
		closesocket(sclient);
		return 0;
	}
	for (int i = 0; i < 1000; i++)
	{
		char * sendData = "csi接收  二进制文件未解析\n";
		send(sclient, sendData, strlen(sendData), 0);
	}
	closesocket(sclient);
	WSACleanup();
	return 0;
}
