#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
void InputNumber(int* num);
int CheckSameNum(int* input, int* rand);
void PrintResult(int same);

int main() {
	int randNum[3] = { 0,0,0 };
	int inputNum[3] = { 0,0,0 };
	int same = 0;

	srand((unsigned int)time(NULL));
	//���� ���� ����
	while (1) {
		for (int i = 0; i < 3; i++) {
			randNum[i] = rand() % 10;
		}
		//���� �Է�
		InputNumber(inputNum);

		system("cls");
		//���߿� ���� ���� �ּ� ó��!
		cout << "���� ���� : " << randNum[0] << " " << randNum[1] << " " << randNum[2] << endl;
		cout << "�Է��� ���� : " << inputNum[0] << " " << inputNum[1] << " " << inputNum[2] << endl;
		
		same = CheckSameNum(inputNum, randNum);
		PrintResult(same);
		same = 0;
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
void PrintResult(int same) {
	switch (same)
	{
	case 0:
		cout << "��Ʈ����ũ" << endl;
		break;
	case 1:
		cout << "��" << endl;
		break;
	case 2:
		cout << "��Ÿ" << endl;
		break;
	case 3:
		cout << "Ȩ��" << endl;
		break;
	default:
		break;
	}
}