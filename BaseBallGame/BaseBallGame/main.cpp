#include <stdlib.h>
#include <cstdio>
#include <WinSock2.h>
void ErrorHandling(const char* errorMsg);
int main() {
	WSADATA wsaData;
	SOCKET hSocket;
	SOCKADDR_IN servAddr;

	char message[30] = {0};
	int size = 0;

	if(WSAStartup(MAKEWORD(2,2), &wsaData)){
		ErrorHandling("WSAStartup() error");
	}

	hSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET) {
		ErrorHandling("socket() error");
	}

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = PF_INET;
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servAddr.sin_port = htons(10000);

	if (connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) {
		ErrorHandling("connect() error");
	}

	size = recv(hSocket, message, sizeof(message)-1, 0);
	if (size == -1) {
		ErrorHandling("recv() error");
	}
	
	printf("server-> %s", message);
	closesocket(hSocket);
	WSACleanup();
	system("pause");
	return 0;

}

void ErrorHandling(const char * errorMsg)
{
	fputs(errorMsg, stderr);
	fputc('\n', stderr);
}
