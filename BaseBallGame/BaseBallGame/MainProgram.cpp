#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
using namespace std;
void InputNumber(int* num);
int CheckSameNum(int* input, int* rand);
void PrintResult(int same, int* teamVal, int* turn, int* round);
void DrawGround(int i);
int mainProgram() {
	int randNum[3] = { 0,0,0 };
	int inputNum[3] = { 0,0,0 };
	int same = 0;
	int team[2][4] = { 0 };//[2]:team1/team2 ,[4]:out/strike/lu/score
	int score[2][9] = { 0 };//[2]:team1/team2, 9회차까지의 점수 저장
	int finalScore[2] = { 0 };
	int turn = 0;
	int round = 1;
	srand((unsigned int)time(NULL));
	//랜덤 숫자 생성
	while (round<10) {
		cout << "===========================" << endl;
		cout <<"["<< round << "회차]" << endl;
		if (turn == 0) {
			cout << "A 팀" << endl;
		}
		else {
			cout << "B 팀" << endl;
		}
		for (int i = 0; i < 3; i++) {
			randNum[i] = rand() % 10;
		}
		//숫자 입력
		//InputNumber(inputNum);
		for (int i = 0; i < 3; i++) {
			inputNum[i] = rand() % 10;
		}
		system("cls");
		cout << "[" << round << "회차]" << endl;
		//회차별 점수 출력
		cout << " │A팀│";
		for (int i = 0; i < round; i++) {
			cout.width(3);
			cout.fill(' ');
			cout <<score[0][i]<<"│";
		}
		cout << "총점 ";
		cout.width(4);
		cout.fill(' ');
		cout<< finalScore[0] << "│" << endl;
		cout << " │B팀│";
		for (int i = 0; i < round; i++) {
			cout.width(3);
			cout.fill(' ');
			cout <<  score[1][i] << "│";
		}
		cout << "총점 ";
		cout.width(4);
		cout.fill(' ');
		cout << finalScore[1] << "│" << endl;
		if (turn == 0) {
			cout << "A 팀  " << team[0][0]<<"아웃"<<endl;
		}
		else {
			cout << "B 팀  " << team[1][0] << "아웃"<< endl;
		}
		int saveTrun = turn;
		int saveRound = round-1;
		//나중에 랜덤 숫자 주석 처리!
		cout << "랜덤 숫자 : " << randNum[0] << " " << randNum[1] << " " << randNum[2] << endl;
		cout << "입력한 숫자 : " << inputNum[0] << " " << inputNum[1] << " " << inputNum[2] << endl;
		same = CheckSameNum(inputNum, randNum);
		PrintResult(same, team[turn], &turn, &round);
		DrawGround(team[saveTrun][2]);
		score[saveTrun][saveRound] = team[saveTrun][3];
		if (saveTrun != turn) {
			team[saveTrun][3] = 0;
		}
		finalScore[saveTrun] = 0;
		for (int i = 0; i <= saveRound; i++) {
			finalScore[saveTrun] += score[saveTrun][i];
		}
		same = 0;
	}

	cout << "게임 종료!" << endl;
	if (finalScore[0] > finalScore[1]) {
		cout << "A팀 승리!" << endl;
	}
	else {
		cout << "B팀 승리!" << endl;
	}

	system("pause");
	return 0;
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
int CheckSameNum(int* input, int* rand){
	int same = 0;
	for (int i = 0; i < 3; i++) {
		if (input[0] == rand[i]) {
			same++;
		}
	}
	if (input[1] != input[0]) {
		for (int i = 0; i < 3; i++) {
			if (input[1] == rand[i]) {
				same++;
			}
		}
	}
	if (input[2] != input[0]&& input[2] != input[1]) {
		for (int i = 0; i < 3; i++) {
			if (input[2] == rand[i]) {
				same++;
			}
		}
	}
	return same;
}
void PrintResult(int same, int* teamVal, int* turn, int* round) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	switch (same)
	{
	case 0:
		cout << "     스트라이크" << endl;
		teamVal[1]++;
		if (teamVal[1] == 3) {
			teamVal[0]++;
			cout <<"     "<< teamVal[0] << " 아웃!" << endl;
			teamVal[1] = 0;
			if (teamVal[0] == 3) {
				teamVal[0] = 0;
				if (*turn == 0) {
					*turn = 1;
				}
				else {
					*turn = 0;
					*round=(*round)+1;
				}
				cout <<"     팀 변경" << endl;
			}
		}
		break;
	case 1:
		cout << "     볼" << endl;
		break;
	case 2:
		cout << "     안타" << endl;
		teamVal[2]++;
		if (teamVal[2] == 4) {
			teamVal[3]++;
			cout << "     1점 획득!    " << "총점  : " << teamVal[3] << endl;
			teamVal[2]--;
		}
		break;
	case 3:
		cout << "     홈런" << endl;
		teamVal[3] += teamVal[2] + 1;
		cout << "     "<<teamVal[2] + 1 << "점 획득!    " << "총점  : " << teamVal[3] << endl;
		teamVal[2] = 0;
		break;
	default:
		break;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
void DrawGround(int i) {
	switch (i)
	{
	case 1:
		cout << "  ○────────●" << endl;
		cout << "  │                │" << endl;
		cout << "  │                │" << endl;
		cout << "  ○────────＠" << endl;
		break;
	case 2:
		cout << "  ●────────●" << endl;
		cout << "  │                │" << endl;
		cout << "  │                │" << endl;
		cout << "  ○────────＠" << endl;
		break;
	case 3:
		cout << "  ●────────●" << endl;
		cout << "  │                │" << endl;
		cout << "  │                │" << endl;
		cout << "  ●────────＠" << endl;
		break;
	default:
		cout << "  ○────────○" << endl;
		cout << "  │                │" << endl;
		cout << "  │                │" << endl;
		cout << "  ○────────＠" << endl;
		break;
	}
}