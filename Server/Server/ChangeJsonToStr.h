#pragma once
#include "rapidjson/document.h"
using namespace rapidjson;
class ChangeJsonToStr
{
public:
	ChangeJsonToStr();
	~ChangeJsonToStr();
	char* GetHomerunStr(int getScore, int totalScore, int roundScore, bool clntTurn, int randNum[], int inputNum[]);
	char* GetStrikeStr(bool out, bool changeTurn, int randNum[], int inputNum[], int round, int lu);
	char* GetBallStr(bool clntTurn, int randNum[], int inputNum[], int lu);
	char* GetHitStr(bool getScore, int totalScore,int lu, bool clntTurn, int randNum[], int inputNum[]);
private:
	Document document;
};

