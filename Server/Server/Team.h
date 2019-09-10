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
	bool SetHit();//true : +1��
	int SetHomeRun();//ȹ���� ���� ��ȯ
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

