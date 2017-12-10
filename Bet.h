#pragma once
#include "defined_code.h"

class Bet
{
public:
	Bet();
	int getLeftBet() const;
	int getBetInUse() const;
	bool addBet(int adds = -1);
	bool setBet(int bet);
	bool tryAddBet(int adds = -1) const;
	void afterJudgeSetBet(GameResult result, float times, bool isPlayerJudge = false, int bet_amount = -1);
	bool canStartGame() const;
	void resetBet();
private:
	bool canAddBet(int adds) const;
	bool canSetBet(int bet) const;
	int amount;
	int betInUse;
};
