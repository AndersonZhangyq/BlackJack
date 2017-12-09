#include "stdafx.h"
#include "Bet.h"
#include "Printer.h"

Bet::Bet()
{
	amount = 1000;
	betInUse = 0;
}

int Bet::getLeftBet() const
{
	return amount;
}

bool Bet::canAddBet(int adds) const
{
	return amount >= adds;
}

bool Bet::canSetBet(int bet) const
{
	return bet <= amount;
}

int Bet::getBetInUse() const
{
	return betInUse;
}

bool Bet::addBet(int adds)
{
	if (adds == -1)
		adds = betInUse;
	if (canAddBet(adds) == false)
	{
		Printer::addBet(false, amount, adds);
		return false;
	}
	amount -= adds;
	betInUse += adds;
	Printer::addBet(true, amount, betInUse);
	return true;
}

bool Bet::setBet(int bet)
{
	if (canSetBet(bet))
	{
		amount = amount - bet;
		betInUse += bet;
		Printer::setBet(true, bet, this->amount);
		return true;
	}
	Printer::setBet(false, bet, this->amount);
	return false;
}

bool Bet::tryAddBet(int adds) const
{
	if (adds == -1)
		adds = betInUse;
	return canAddBet(adds);
}

void Bet::endGameSet(GameResult resullt, float times)
{
	switch (resullt)
	{
	case Win:
		amount += times * betInUse;
		break;
	case Lose:
		amount -= (times - 1) * betInUse;
		break;
	case Draw:
		amount += betInUse;
		break;
	}
	betInUse = 0;
}

bool Bet::canStartGame() const
{
	return amount > 0;
}
