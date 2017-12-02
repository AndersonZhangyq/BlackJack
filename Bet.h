#pragma once
class Bet
{
public:
	Bet();
	int getLeftBet();
	bool couldDoubleBet();
	int getBetInUse();
	bool doubleBet();
private:
	int amount;
	int betInUse;

};