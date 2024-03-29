#include "PrintResult.h"



PrintResult::PrintResult()
{
}


PrintResult::~PrintResult()
{
}

void PrintResult::ReadJsonData(const char str[])
{
	Document d;
	d.Parse(str);
	//⑷營 �蜃�
	printf("[%d�蜃躕\n", d["round"].GetInt());
	//�蜃鷚� 薄熱 塽 識薄 轎溘
	printf("弛Clnt弛");
	for(auto& val: d["roundScoreClnt"].GetArray()){
		printf("%3d弛", val.GetInt());
	}
	printf("識薄 %5d弛\n", d["totalScoreClnt"].GetInt());
	printf("弛Serv弛");
	for (auto& val : d["roundScoreServ"].GetArray()) {
		printf("%3d弛", val.GetInt());
	}
	printf("識薄 %5d弛\n", d["totalScoreServ"].GetInt());
	//⑷營 ぜ 轎溘
	if (d["clntTurn"].GetBool()) {
		printf("Client Team\n");
	}
	else {
		printf("Server Team\n");
	}
	PrintLu(d["lu"].GetInt());
	printf("random number : %d %d %d\n", d["randNum"][0].GetInt(), d["randNum"][1].GetInt(), d["randNum"][2].GetInt());
	printf("input number : %d %d %d\n", d["inputNum"][0].GetInt(), d["inputNum"][1].GetInt(), d["inputNum"][2].GetInt());

	for (auto& val : d["result"].GetArray()) {
		printf("%s\n", val.GetString());
	}
}

void PrintResult::PrintLu(int lu)
{
	switch (lu)
	{
	case 1:
		printf("  ∞式式式式式式式式≒\n");
		printf("  弛                弛\n");
		printf("  弛                弛\n");
		printf("  ∞式式式式式式式式�餐n");
		break;
	case 2:
		printf("  ≒式式式式式式式式≒\n");
		printf("  弛                弛\n");
		printf("  弛                弛\n");
		printf("  ∞式式式式式式式式�餐n");
		break;
	case 3:
		printf("  ≒式式式式式式式式≒\n");
		printf("  弛                弛\n");
		printf("  弛                弛\n");
		printf("  ≒式式式式式式式式�餐n");
		break;
	default:
		printf("  ∞式式式式式式式式∞\n");
		printf("  弛                弛\n");
		printf("  弛                弛\n");
		printf("  ∞式式式式式式式式�餐n");
		break;
	}
}
