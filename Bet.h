#pragma once
#include "defined_code.h"

class Bet
{
public:
	Bet();
	int getLeftBet() const;
	int getBetInUse() const;
	bool doubleBet();
	bool setBet(int bet);
	bool tryDouble() const;
	void endGameSet(GameResult result, float times);
	bool canStartGame() const;
private:
	bool canDoubleBet() const;
	bool canSetBet(int bet) const;
	int amount;
	int betInUse;
};
