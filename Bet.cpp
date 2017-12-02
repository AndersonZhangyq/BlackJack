#include "stdafx.h"
#include "Bet.h"

Bet::Bet()
{
	amount = 1000;
	betInUse = 0;
}

int Bet::getLeftBet()
{
	return amount;
}

bool Bet::couldDoubleBet()
{
	return amount > 2 * betInUse;
}

int Bet::getBetInUse()
{
	return betInUse;
}

bool Bet::doubleBet()
{
	if (couldDoubleBet() == false)
		return false;
	amount -= 2 * betInUse;
	betInUse *= 2;
	return true;
}
