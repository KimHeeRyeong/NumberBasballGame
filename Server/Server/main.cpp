#include <stdlib.h>
#include <cstdio>
#include <WinSock2.h>
#include "Team.h"
#include "CheckNumber.h"
#include "ChangeJsonToStr.h"
#include "PrintResult.h"
void ErrorHandling(const char* errorMsg);
int main() {
	srand((unsigned int)time(NULL));
	Team tServ, tClnt;
	Team* playTeam;//현재 플레이중인 팀
	CheckNumber randNum;
	ChangeJsonToStr changeStr;
	PrintResult printResult;
	int inputNum[3] = { 0 };
	bool clntTurn = true;

	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAddr, clntAddr;

	int szClntAddr;
	char message[] = "Hello!";
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		ErrorHandling("WSAStartup() error");
	}

	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	if (hServSock == INVALID_SOCKET) {
		ErrorHandling("socket() error");
	}

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(ADDR_ANY);
	servAddr.sin_port = htons(10000);

	if (bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) {
		ErrorHandling("bind() error");
	}

	if (listen(hServSock, 5) == SOCKET_ERROR) {
		ErrorHandling("listen() error");
	}
	
	szClntAddr = sizeof(clntAddr);
	hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &szClntAddr);
	if (hClntSock == INVALID_SOCKET) {
		ErrorHandling("accept() error");
	}
	int round = 0;
	playTeam = &tClnt;
	while (round<9) {
		//1)input num or recv num
		for (int i = 0; i < 3; i++) {
			inputNum[i] = rand() % 10;
		}
		//2)compare and getResult
		Result result = randNum.CheckNum(inputNum);
		switch (result)
		{
		case STR:
		{
			StrikeState strikeState = playTeam->SetStrike();
			switch (strikeState)
			{
			case STRIKE:
				break;
			case GAMEOUT:
				break;
			case TEAMCHANGE:
				if(!clntTurn){
					round++;
					playTeam = &tClnt;
					clntTurn = true;
				}else{
					playTeam = &tServ;
					clntTurn = false;
				}
				break;
			}
			break; 
		}
		case BALL:
			break;
		case HIT:
			break;
		case HOMERUN:
			int getScore = playTeam->SetHomeRun();
			char* str = changeStr.GetHomerunStr(getScore, playTeam->GetTotalScore(), 
				playTeam->GetRoundScore(), clntTurn, randNum.GetRandNum(), inputNum);
			int length = strlen(str) + 1;
			send(hClntSock, str, length, 0);
			free(str);
			break;
		}
	}
	
	closesocket(hClntSock);
	closesocket(hServSock);
	WSACleanup();
	system("pause");
	return 0;
}
void ErrorHandling(const char * errorMsg)
{
	fputs(errorMsg, stderr);
	fputc('\n', stderr);
	exit(1);
}
