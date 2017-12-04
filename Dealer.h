#pragma once
#include "Bet.h"
#include "Hand.h"
#include "Card.h"
#include <vector>

class BlackJackGame;

class Dealer{
public:
	Dealer();
	Dealer(BlackJackGame game);
	std::string getHandDescriptionString() const;
	bool isBlackJack() const;
	void addCard(Card card) const;
	int getBest() const;
	std::vector<int> getCardTotal() const;
	void reset();
private:
	Hand* hand_;
	BlackJackGame* game_;
};
