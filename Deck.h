#pragma once
#include "Card.h"
#include <vector>

class Deck {
public:
	Deck();
	Deck(int deckNumber);
	Card getCard();
	void restore();
private:
	int deckNumber;

	std::vector<std::vector<int>> allCards;
};