#pragma once
enum StrikeState {
	STRIKE,
	GAMEOUT,
	TEAMCHANGE
};
class Team
{
public:
	Team();
	~Team();
	StrikeState SetStrike();
	bool SetHit();//true : +1Á¡
	int SetHomeRun();//È¹µæÇÑ Á¡¼ö ¹ÝÈ¯
	int GetRoundScore();
	int GetTotalScore();
private:
	int strike;
	int out;
	int lu;
	int roundScore;
	int score;//total score;

	void ChangeTeam();
};

