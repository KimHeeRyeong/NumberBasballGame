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
	int score[2][9] = { 0 };//[2]:team1/team2, 9ȸ�������� ���� ����
	int finalScore[2] = { 0 };
	int turn = 0;
	int round = 1;
	srand((unsigned int)time(NULL));
	//���� ���� ����
	while (round<10) {
		cout << "===========================" << endl;
		cout <<"["<< round << "ȸ��]" << endl;
		if (turn == 0) {
			cout << "A ��" << endl;
		}
		else {
			cout << "B ��" << endl;
		}
		for (int i = 0; i < 3; i++) {
			randNum[i] = rand() % 10;
		}
		//���� �Է�
		//InputNumber(inputNum);
		for (int i = 0; i < 3; i++) {
			inputNum[i] = rand() % 10;
		}
		system("cls");
		cout << "[" << round << "ȸ��]" << endl;
		//ȸ���� ���� ���
		cout << " ��A����";
		for (int i = 0; i < round; i++) {
			cout.width(3);
			cout.fill(' ');
			cout <<score[0][i]<<"��";
		}
		cout << "���� ";
		cout.width(4);
		cout.fill(' ');
		cout<< finalScore[0] << "��" << endl;
		cout << " ��B����";
		for (int i = 0; i < round; i++) {
			cout.width(3);
			cout.fill(' ');
			cout <<  score[1][i] << "��";
		}
		cout << "���� ";
		cout.width(4);
		cout.fill(' ');
		cout << finalScore[1] << "��" << endl;
		if (turn == 0) {
			cout << "A ��  " << team[0][0]<<"�ƿ�"<<endl;
		}
		else {
			cout << "B ��  " << team[1][0] << "�ƿ�"<< endl;
		}
		int saveTrun = turn;
		int saveRound = round-1;
		//���߿� ���� ���� �ּ� ó��!
		cout << "���� ���� : " << randNum[0] << " " << randNum[1] << " " << randNum[2] << endl;
		cout << "�Է��� ���� : " << inputNum[0] << " " << inputNum[1] << " " << inputNum[2] << endl;
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

	cout << "���� ����!" << endl;
	if (finalScore[0] > finalScore[1]) {
		cout << "A�� �¸�!" << endl;
	}
	else {
		cout << "B�� �¸�!" << endl;
	}

	system("pause");
	return 0;
}
void InputNumber(int* num) {
	cout << "���ڸ� �Է����ּ���(0~9, �ߺ� ����)" << endl;
	for (int i = 0; i < 3; i++) {
		cin >> num[i];
		if (cin.fail()) {
			cout << "���ڸ� �Է����ּ���!" << endl;
			cin.clear();
			cin.ignore();
			i--;
		}
		else if (num[i] > 9 || num[i] < 0) {
			cout << "������ ������ 0~9�Դϴ�!" << endl;
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
		cout << "     ��Ʈ����ũ" << endl;
		teamVal[1]++;
		if (teamVal[1] == 3) {
			teamVal[0]++;
			cout <<"     "<< teamVal[0] << " �ƿ�!" << endl;
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
				cout <<"     �� ����" << endl;
			}
		}
		break;
	case 1:
		cout << "     ��" << endl;
		break;
	case 2:
		cout << "     ��Ÿ" << endl;
		teamVal[2]++;
		if (teamVal[2] == 4) {
			teamVal[3]++;
			cout << "     1�� ȹ��!    " << "����  : " << teamVal[3] << endl;
			teamVal[2]--;
		}
		break;
	case 3:
		cout << "     Ȩ��" << endl;
		teamVal[3] += teamVal[2] + 1;
		cout << "     "<<teamVal[2] + 1 << "�� ȹ��!    " << "����  : " << teamVal[3] << endl;
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
		cout << "  �ۦ�����������������" << endl;
		cout << "  ��                ��" << endl;
		cout << "  ��                ��" << endl;
		cout << "  �ۦ�����������������" << endl;
		break;
	case 2:
		cout << "  �ܦ�����������������" << endl;
		cout << "  ��                ��" << endl;
		cout << "  ��                ��" << endl;
		cout << "  �ۦ�����������������" << endl;
		break;
	case 3:
		cout << "  �ܦ�����������������" << endl;
		cout << "  ��                ��" << endl;
		cout << "  ��                ��" << endl;
		cout << "  �ܦ�����������������" << endl;
		break;
	default:
		cout << "  �ۦ�����������������" << endl;
		cout << "  ��                ��" << endl;
		cout << "  ��                ��" << endl;
		cout << "  �ۦ�����������������" << endl;
		break;
	}
}