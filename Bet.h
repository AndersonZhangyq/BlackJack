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
	void endGameSet(GameResult result, float times);
	bool canStartGame() const;
private:
	bool canAddBet(int adds) const;
	bool canSetBet(int bet) const;
	int amount;
	int betInUse;
};
