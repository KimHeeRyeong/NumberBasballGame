#include <iostream>

using namespace std;
int main() {
	int randNum[3] = { 0,0,0 };
	int inputNum[3] = { 0,0,0 };
	cout << "==========================" << endl;
	cout << "���ڸ� �Է����ּ���(0~9, �ߺ� ����)" << endl;
	for (int i = 0; i < 3; i++) {
		cin >> inputNum[i];
		if (cin.fail()) {
			cout << "���ڸ� �Է����ּ���!"<<endl;
			cin.clear();
			cin.ignore();
			i--;
		}
		else if (inputNum[i] > 9 || inputNum[i] < 0) {
			cout << "������ ������ 0~9�Դϴ�!" << endl;
			i--;
		}
	}
	cout << "�Է��� ���� : " << inputNum[0] << " " << inputNum[1] << " " << inputNum[2]<<endl;

	system("pause");
	return 0;
}