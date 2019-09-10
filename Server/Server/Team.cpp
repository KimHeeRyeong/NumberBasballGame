#include "Team.h"



Team::Team()
{
	strike = 0;
	out = 0;
	lu = 0;
	roundScore = 0;
	score = 0;
}


Team::~Team()
{
}

StrikeState Team::SetStrike()
{
	strike++;
	if (strike == 3) {
		out++;
		strike = 0;
		if (out == 3) {
			ChangeTeam();
			return TEAMCHANGE;
		}
		return GAMEOUT;
	}
	return STRIKE;
}

bool Team::SetHit()
{
	lu++;
	if (lu == 4) {
		roundScore++;
		score++;
		lu = 0;
		return true;
	}
	return false;
}

int Team::SetHomeRun()
{
	int save = lu + 1;
	lu = 0;
	score += save;
	roundScore += save;
	return save;
}

int Team::GetRoundScore()
{
	return roundScore;
}

int Team::GetTotalScore()
{
	return score;
}

void Team::ChangeTeam()
{
	roundScore = 0;
	out = 0;
}
