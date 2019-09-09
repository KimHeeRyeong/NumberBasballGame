#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
void InputNumber(int* num);
int CheckSameNum(int* input, int* rand);
void PrintResult(int same, int* teamVal, int* turn, int* round);

int main() {
	int randNum[3] = { 0,0,0 };
	int inputNum[3] = { 0,0,0 };
	int same = 0;
	int team[2][4] = { 0 };//[2]:team1/team2 ,[4]:out/strike/lu/score
	int turn = 0;
	int round = 1;
	srand((unsigned int)time(NULL));
	//랜덤 숫자 생성
	while (1) {
		cout << "===========================" << endl;
		cout << round << "회차" << endl;
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
		InputNumber(inputNum);

		system("cls");
		cout << round << "회차" << endl;
		if (turn == 0) {
			cout << "A 팀" << endl;
		}
		else {
			cout << "B 팀" << endl;
		}
		//나중에 랜덤 숫자 주석 처리!
		cout << "랜덤 숫자 : " << randNum[0] << " " << randNum[1] << " " << randNum[2] << endl;
		cout << "입력한 숫자 : " << inputNum[0] << " " << inputNum[1] << " " << inputNum[2] << endl;
		
		same = CheckSameNum(inputNum, randNum);
		PrintResult(same, team[turn], &turn,&round);
		same = 0;
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
	switch (same)
	{
	case 0:
		cout << "스트라이크" << endl;
		teamVal[1]++;
		if (teamVal[1] == 3) {
			teamVal[0]++;
			cout << teamVal[0] << "아웃!" << endl;
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
				cout <<"팀 변경" << endl;
			}
		}
		break;
	case 1:
		cout << "볼" << endl;
		break;
	case 2:
		cout << "안타" << endl;
		teamVal[2]++;
		if (teamVal[2] == 4) {
			teamVal[3]++;
			cout << "1점 획득!    " << "총점  : " << teamVal[3] << endl;
			teamVal[2]--;
		}
		break;
	case 3:
		cout << "홈런" << endl;
		teamVal[3] += teamVal[2] + 1;
		cout << teamVal[2] + 1 << "점 획득!    " << "총점  : " << teamVal[3] << endl;
		teamVal[2] = 0;
		break;
	default:
		break;
	}
}