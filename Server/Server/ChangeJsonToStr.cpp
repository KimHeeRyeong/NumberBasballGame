#include "ChangeJsonToStr.h"
#include <rapidjson/writer.h>
#include <stdlib.h>
ChangeJsonToStr::ChangeJsonToStr()
{
	document.SetObject();
	document.AddMember("round", Value().SetInt(0), document.GetAllocator());

	document.AddMember("roundScoreClnt", Value().SetArray(), document.GetAllocator());
	document.AddMember("totalScoreClnt", Value().SetInt(0), document.GetAllocator());
	document.AddMember("roundScoreServ", Value().SetArray(), document.GetAllocator());
	document.AddMember("totalScoreServ", Value().SetInt(0), document.GetAllocator());

	document.AddMember("lu", Value().SetInt(0), document.GetAllocator());

	document.AddMember("randNum", Value().SetArray(), document.GetAllocator());
	document.AddMember("inputNum", Value().SetArray(), document.GetAllocator());
	for (int i = 0; i < 3; i++) {
		document["randNum"].PushBack(Value().SetInt(0), document.GetAllocator());
		document["inputNum"].PushBack(Value().SetInt(0), document.GetAllocator());
	}

	document.AddMember("result", Value().SetArray(), document.GetAllocator());

	document.AddMember("clntTurn", Value().SetBool(false), document.GetAllocator());
}


ChangeJsonToStr::~ChangeJsonToStr()
{
}

char * ChangeJsonToStr::GetHomerunStr(int getScore, int totalScore, int roundScore, bool clntTurn, int randNum[], int inputNum[])
{
	int round = document["round"].GetInt();
	if (document["roundScoreClnt"].GetArray().Size() == round) {
		document["roundScoreClnt"].PushBack(Value().SetInt(0), document.GetAllocator());
		document["roundScoreServ"].PushBack(Value().SetInt(0), document.GetAllocator());
	}
	if (clntTurn) {
		document["roundScoreClnt"][round].SetInt(roundScore);
		document["totalScoreClnt"].SetInt(totalScore);
	}
	else {
		document["roundScoreServ"][round].SetInt(roundScore);
		document["totalScoreServ"].SetInt(totalScore);
	}
	document["lu"].SetInt(0);

	document["result"].PushBack(Value().SetString("È¨·±!", document.GetAllocator()), document.GetAllocator());
	char score[50],
		next[] = "Á¡ È¹µæ";
	_itoa(getScore,score,10);
	strcat(score,next);
	document["result"].PushBack(Value().SetString(score, document.GetAllocator()), document.GetAllocator());
	document["clntTurn"].SetBool(false);
	for (int i = 0; i < 3; i++) {
		document["randNum"][i].SetInt(randNum[i]);
		document["inputNum"][i].SetInt(inputNum[i]);
	}
	StringBuffer buffer;
	buffer.Clear();

	Writer<StringBuffer> writer(buffer);
	document.Accept(writer);
	document["result"].GetArray().Clear();
	return _strdup(buffer.GetString());
}
