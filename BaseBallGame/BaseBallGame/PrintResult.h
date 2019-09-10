#pragma once
#include "rapidjson/document.h"
using namespace rapidjson;
class PrintResult
{
public:
	PrintResult();
	~PrintResult();
	void ReadJsonData(const char str[], bool* clntTurn);
private:
	void PrintLu(int lu);
};

