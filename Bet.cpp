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

bool Bet::canDoubleBet() const
{
	return amount >= betInUse;
}

bool Bet::canSetBet(int bet) const
{
	return bet <= amount;
}

int Bet::getBetInUse() const
{
	return betInUse;
}

bool Bet::doubleBet()
{
	if (canDoubleBet() == false)
	{
		Printer::doubleBet(false, amount, betInUse);
		return false;
	}
	amount -= betInUse;
	betInUse *= 2;
	Printer::doubleBet(true, amount, betInUse);
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

bool Bet::tryDouble() const
{
	return canDoubleBet();
}

void Bet::endGameSet(GameResult resullt, float times)
{
	switch (resullt)
	{
	case Win:
		amount += times * betInUse;
		break;
	case Lose:
		amount -= times * betInUse;
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
