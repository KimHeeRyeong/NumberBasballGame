#pragma once
#include <cstdlib>
#include <ctime>
using namespace std;
enum Result
{
	STR,
	BALL,
	HIT,
	HOMERUN
};
class CheckNumber
{
public:
	CheckNumber();
	~CheckNumber();
	Result CheckNum(int* input);
	int* GetRandNum();
private:
	int randNum[3];

	int CntSameNum(int* input);
	void SetRandom();
};

