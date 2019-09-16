#include "PrintResult.h"



PrintResult::PrintResult()
{
}


PrintResult::~PrintResult()
{
}

bool PrintResult::ReadJsonData(const char str[], bool* clntTurn)
{
	Document d;
	d.Parse(str);
	//ÇöÀç È¸Â÷
	printf("[%dÈ¸Â÷]\n", d["round"].GetInt());
	//È¸Â÷º° Á¡¼ö ¹× ÃÑÁ¡ Ãâ·Â
	printf("¦¢Clnt¦¢");
	for(auto& val: d["roundScoreClnt"].GetArray()){
		printf("%3d¦¢", val.GetInt());
	}
	printf("ÃÑÁ¡ %5d¦¢\n", d["totalScoreClnt"].GetInt());
	printf("¦¢Serv¦¢");
	for (auto& val : d["roundScoreServ"].GetArray()) {
		printf("%3d¦¢", val.GetInt());
	}
	printf("ÃÑÁ¡ %5d¦¢\n", d["totalScoreServ"].GetInt());
	//ÇöÀç ÆÀ Ãâ·Â
	if (d["clntTurn"].GetBool()) {
		*clntTurn = true;
		printf("Client Team\n");
	}
	else {
		*clntTurn = false;
		printf("Server Team\n");
	}
	PrintLu(d["lu"].GetInt());
	printf("random number : %d %d %d\n", d["randNum"][0].GetInt(), d["randNum"][1].GetInt(), d["randNum"][2].GetInt());
	printf("input number : %d %d %d\n", d["inputNum"][0].GetInt(), d["inputNum"][1].GetInt(), d["inputNum"][2].GetInt());

	for (auto& val : d["result"].GetArray()) {
		printf("%s\n", val.GetString());
	}
	if (d["changeTurn"].GetBool()) {
		*clntTurn = !(*clntTurn);
		if (d["round"].GetInt() == 8 && *clntTurn) {
			return true;
		}
	}
	return false;
}

void PrintResult::PrintLu(int lu)
{
	switch (lu)
	{
	case 1:
		printf("  ¡Û¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¡Ü\n");
		printf("  ¦¢                ¦¢\n");
		printf("  ¦¢                ¦¢\n");
		printf("  ¡Û¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡£À\n");
		break;
	case 2:
		printf("  ¡Ü¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¡Ü\n");
		printf("  ¦¢                ¦¢\n");
		printf("  ¦¢                ¦¢\n");
		printf("  ¡Û¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡£À\n");
		break;
	case 3:
		printf("  ¡Ü¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¡Ü\n");
		printf("  ¦¢                ¦¢\n");
		printf("  ¦¢                ¦¢\n");
		printf("  ¡Ü¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡£À\n");
		break;
	default:
		printf("  ¡Û¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¡Û\n");
		printf("  ¦¢                ¦¢\n");
		printf("  ¦¢                ¦¢\n");
		printf("  ¡Û¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡£À\n");
		break;
	}
}
