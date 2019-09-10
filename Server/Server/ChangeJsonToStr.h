#pragma once
#include "rapidjson/document.h"
using namespace rapidjson;
class ChangeJsonToStr
{
public:
	ChangeJsonToStr();
	~ChangeJsonToStr();
	char* GetHomerunStr(int getScore, int totalScore, int roundScore, bool clntTurn, int randNum[], int inputNum[]);
	char* GetStrikeStr(bool out, bool change);
	char* GetBallStr();
	char* GetHitStr(bool getScore, int totalScore, int roundScore);
private:
	Document document;
};

