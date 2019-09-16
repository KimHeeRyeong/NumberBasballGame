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

	document.AddMember("clntTurn", Value().SetBool(true), document.GetAllocator());

	document.AddMember("changeTurn", Value().SetBool(false), document.GetAllocator());
}


ChangeJsonToStr::~ChangeJsonToStr()
{
	document.RemoveAllMembers();
	document.Clear();
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

	document["result"].PushBack(Value().SetString("»®∑±!", document.GetAllocator()), document.GetAllocator());
	char score[50],
		next[] = "¡° »πµÊ";
	_itoa(getScore,score,10);
	strcat(score,next);
	document["result"].PushBack(Value().SetString(score, document.GetAllocator()), document.GetAllocator());
	document["clntTurn"].SetBool(clntTurn);
	for (int i = 0; i < 3; i++) {
		document["randNum"][i].SetInt(randNum[i]);
		document["inputNum"][i].SetInt(inputNum[i]);
	}
	document["changeTurn"].SetBool(false);
	StringBuffer buffer;
	buffer.Clear();

	Writer<StringBuffer> writer(buffer);
	document.Accept(writer);
	document["result"].GetArray().Clear();
	return _strdup(buffer.GetString());
}

char * ChangeJsonToStr::GetStrikeStr(bool out, bool changeTurn, int randNum[], int inputNum[], int round, int lu)
{
	if (document["roundScoreClnt"].GetArray().Size() == round) {
		document["roundScoreClnt"].PushBack(Value().SetInt(0), document.GetAllocator());
		document["roundScoreServ"].PushBack(Value().SetInt(0), document.GetAllocator());
	}
	document["result"].PushBack(Value().SetString("Ω∫∆Æ∂Û¿Ã≈©", document.GetAllocator()), document.GetAllocator());
	if (out) {
		document["result"].PushBack(Value().SetString("+1æ∆øÙ", document.GetAllocator()), document.GetAllocator());
	}
	document["changeTurn"].SetBool(changeTurn);
	if (changeTurn) {
		document["result"].PushBack(Value().SetString("∆¿ ∫Ø∞Ê", document.GetAllocator()), document.GetAllocator());
		document["round"].SetInt(round);
	}
	for (int i = 0; i < 3; i++) {
		document["randNum"][i].SetInt(randNum[i]);
		document["inputNum"][i].SetInt(inputNum[i]);
	}
	document["lu"].SetInt(lu);
	StringBuffer buffer;
	buffer.Clear();

	Writer<StringBuffer> writer(buffer);
	document.Accept(writer);
	document["result"].GetArray().Clear();
	if (changeTurn) {
		bool save = document["clntTurn"].GetBool();
		document["clntTurn"].SetBool(!save);
		if (!save) {
			document["round"].SetInt(round + 1);
		}
	}
	return _strdup(buffer.GetString());
}

char * ChangeJsonToStr::GetBallStr(bool clntTurn, int randNum[], int inputNum[], int lu)
{
	int round = document["round"].GetInt();
	if (document["roundScoreClnt"].GetArray().Size() == round) {
		document["roundScoreClnt"].PushBack(Value().SetInt(0), document.GetAllocator());
		document["roundScoreServ"].PushBack(Value().SetInt(0), document.GetAllocator());
	}
	document["result"].PushBack(Value().SetString("∫º", document.GetAllocator()), document.GetAllocator());
	document["clntTurn"].SetBool(clntTurn);
	for (int i = 0; i < 3; i++) {
		document["randNum"][i].SetInt(randNum[i]);
		document["inputNum"][i].SetInt(inputNum[i]);
	}
	document["lu"].SetInt(lu);
	document["changeTurn"].SetBool(false);
	StringBuffer buffer;
	buffer.Clear();

	Writer<StringBuffer> writer(buffer);
	document.Accept(writer);
	document["result"].GetArray().Clear();
	return _strdup(buffer.GetString());
}

char * ChangeJsonToStr::GetHitStr(bool getScore, int totalScore,int lu, bool clntTurn, int randNum[], int inputNum[])
{
	int round = document["round"].GetInt();
	if (document["roundScoreClnt"].GetArray().Size() == round) {
		document["roundScoreClnt"].PushBack(Value().SetInt(0), document.GetAllocator());
		document["roundScoreServ"].PushBack(Value().SetInt(0), document.GetAllocator());
	}
	if (getScore) {
		if (clntTurn) {
			int roundScore = document["roundScoreClnt"][round].GetInt()+1;
			document["roundScoreClnt"][round].SetInt(roundScore);
			document["totalScoreClnt"].SetInt(totalScore);
		}
		else {
			int roundScore = document["roundScoreServ"][round].GetInt() + 1;
			document["roundScoreServ"][round].SetInt(roundScore);
			document["totalScoreServ"].SetInt(totalScore);
		}
	}
	document["lu"].SetInt(lu);

	document["result"].PushBack(Value().SetString("æ»≈∏", document.GetAllocator()), document.GetAllocator());
	if (getScore) {
		document["result"].PushBack(Value().SetString("1¡° »πµÊ", document.GetAllocator()), document.GetAllocator());
	}
	document["clntTurn"].SetBool(clntTurn);
	for (int i = 0; i < 3; i++) {
		document["randNum"][i].SetInt(randNum[i]);
		document["inputNum"][i].SetInt(inputNum[i]);
	}
	document["changeTurn"].SetBool(false);
	StringBuffer buffer;
	buffer.Clear();

	Writer<StringBuffer> writer(buffer);
	document.Accept(writer);
	document["result"].GetArray().Clear();
	return _strdup(buffer.GetString());
}
