#include <stdlib.h>
#include <cstdio>
#include <WinSock2.h>
#include "Team.h"
#include "CheckNumber.h"
#include "ChangeJsonToStr.h"
#include "PrintResult.h"
#include <iostream>
void InputNumber(int* num);
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
	char message[500];
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
		if (clntTurn) {
			memset(message, 0, sizeof(message));
			recv(hClntSock, message, sizeof(message)-1, 0);
			Document d;
			d.Parse(message);
			if (d.IsArray()) {
				for (int i = 0; i < 3; i++) {
					inputNum[i] = d[i].GetInt();
				}
			}
			else {
				break;
			}
			d.Clear();
		}
		else {
			//InputNumber(inputNum);
			for (int i = 0; i < 3; i++) {
				inputNum[i] = rand() % 10;
			}
			Sleep(100);
		}
		system("cls");
		//2)compare and getResult
		Result result = randNum.CheckNum(inputNum);
		switch (result)
		{
		case STR:
		{
			StrikeState strikeState = playTeam->SetStrike();
			char* str = {0};
			switch (strikeState)
			{
			case STRIKE:
				str = changeStr.GetStrikeStr(false, false, randNum.GetRandNum(), inputNum,0, playTeam->GetLu());
				break;
			case GAMEOUT:
				printf("GAMEOUT");
				str = changeStr.GetStrikeStr(true, false, randNum.GetRandNum(), inputNum,0, playTeam->GetLu());
				break;
			case TEAMCHANGE:
				printf("TEAMCHANGE");
				if(!clntTurn){
					round++;
					str = changeStr.GetStrikeStr(true, true, randNum.GetRandNum(), inputNum, round, playTeam->GetLu());
					playTeam = &tClnt;
					clntTurn = true;
				}else{
					str = changeStr.GetStrikeStr(true, true, randNum.GetRandNum(), inputNum, round, playTeam->GetLu());
					playTeam = &tServ;
					clntTurn = false;
				}
				break;
			}
			int length = strlen(str) + 1;
			send(hClntSock, str, length, 0);
			printResult.ReadJsonData(str);
			free(str);
			break; 
		}
		case BALL: {
			char* str = changeStr.GetBallStr(clntTurn, randNum.GetRandNum(), inputNum, playTeam->GetLu());
			int length = strlen(str) + 1;
			send(hClntSock, str, length, 0);
			printResult.ReadJsonData(str);
			free(str);
			break; 
		}
		case HIT: {
			bool getScore = playTeam->SetHit();
			char* str = changeStr.GetHitStr(getScore, playTeam->GetTotalScore(), playTeam->GetLu(), clntTurn, randNum.GetRandNum(),inputNum);
			int length = strlen(str) + 1;
			send(hClntSock, str, length, 0);
			printResult.ReadJsonData(str);
			free(str);
			break; 
		}
		case HOMERUN: {
			int getScore = playTeam->SetHomeRun();
			char* str = changeStr.GetHomerunStr(getScore, playTeam->GetTotalScore(),
				playTeam->GetRoundScore(), clntTurn, randNum.GetRandNum(), inputNum);
			int length = strlen(str) + 1;
			send(hClntSock, str, length, 0);
			printResult.ReadJsonData(str);
			free(str);
			break; 
		}
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
void InputNumber(int* num) {
	cout << "숫자를 입력해주세요(0~9, 중복 가능)" << endl;
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
