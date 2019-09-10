#include "CheckNumber.h"



CheckNumber::CheckNumber()
{
	//initailze
	for (int i = 0; i < 3; i++) {
		randNum[i] = 0;
	}
}


CheckNumber::~CheckNumber()
{
}

Result CheckNumber::CheckNum(int * input)
{
	SetRandom();
	int same = CntSameNum(input);
	switch (same)
	{
	case 0:
		return STR;
		break;
	case 1:
		return BALL;
		break;
	case 2:
		return HIT;
		break;
	case3:
		return HOMERUN;
		break;
	}
}

int* CheckNumber::GetRandNum()
{
	return randNum;
}

int CheckNumber::CntSameNum(int * input)
{
	int same = 0;
	for (int i = 0; i < 3; i++) {
		if (input[0] == randNum[i]) {
			same++;
		}
	}
	if (input[1] != input[0]) {
		for (int i = 0; i < 3; i++) {
			if (input[1] == randNum[i]) {
				same++;
			}
		}
	}
	if (input[2] != input[0] && input[2] != input[1]) {
		for (int i = 0; i < 3; i++) {
			if (input[2] == randNum[i]) {
				same++;
			}
		}
	}
	return same;
}

void CheckNumber::SetRandom()
{
	for (int i = 0; i < 3; i++) {
		randNum[i] = rand() % 10;
	}
}
