#include <stdlib.h>
#include <cstdio>
#include <WinSock2.h>
#include <iostream>
#include "PrintResult.h"
#include <rapidjson/writer.h>
using namespace std;
void ErrorHandling(const char* errorMsg);
void InputNumber(int* num);
int main() {
	bool clntTurn = true;
	int round = 0;
	int inputNum[3] = {0};
	PrintResult printResult;
	
	Document sendDoc;
	sendDoc.SetArray();
	for (int i = 0; i < 3; i++) {
		sendDoc.PushBack(Value().SetInt(0), sendDoc.GetAllocator());
	}

	WSADATA wsaData;
	SOCKET hSocket;
	SOCKADDR_IN servAddr;

	char message[500];
	int strLen;

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

	while (round < 9) {
		if (clntTurn) {
			//InputNumber(inputNum);
			for (int i = 0; i < 3; i++) {
				inputNum[i] = rand() % 10;
			}
			Sleep(100);
			for (int i = 0; i < 3; i++) {
				sendDoc[i].SetInt(inputNum[i]);
			}
			StringBuffer buffer;
			buffer.Clear();

			Writer<StringBuffer> writer(buffer);
			sendDoc.Accept(writer);
			char* str = _strdup(buffer.GetString());
			int length = strlen(str) + 1;
			send(hSocket, str, length, 0);
			free(str);
		}
		memset(message, 0, sizeof(message));
		recv(hSocket, message, sizeof(message) - 1, 0);
		system("cls");
		printResult.ReadJsonData(message,&clntTurn);
	}
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
void InputNumber(int* num) {
	cout <<endl<<"숫자를 입력해주세요(0~9, 중복 가능)" << endl;
	for (int i = 0; i < 3; i++) {
		cin >> num[i];
		if (cin.fail()) {
			cout << "숫자만 입력해주세요!" << endl;
			cin.clear();
			cin.ignore();
			i--;
		}
		else if (num[i] > 9 || num[i] < 0) {
			cout << "숫자의 범위는 0~9입니다!" << endl;
			i--;
		}
	}
}
