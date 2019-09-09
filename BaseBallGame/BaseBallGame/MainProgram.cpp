#include <iostream>

using namespace std;
int main() {
	int randNum[3] = { 0,0,0 };
	int inputNum[3] = { 0,0,0 };
	cout << "==========================" << endl;
	cout << "숫자를 입력해주세요(0~9, 중복 가능)" << endl;
	for (int i = 0; i < 3; i++) {
		cin >> inputNum[i];
		if (cin.fail()) {
			cout << "숫자만 입력해주세요!"<<endl;
			cin.clear();
			cin.ignore();
			i--;
		}
		else if (inputNum[i] > 9 || inputNum[i] < 0) {
			cout << "숫자의 범위는 0~9입니다!" << endl;
			i--;
		}
	}
	cout << "입력한 숫자 : " << inputNum[0] << " " << inputNum[1] << " " << inputNum[2]<<endl;

	system("pause");
	return 0;
}