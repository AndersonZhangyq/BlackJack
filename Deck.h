#pragma once
#include <vector>
#include "Card.h"

class Deck {
public:
	Deck();
	Deck(int deckNumber);
	Card getCard();
	bool canDraw();
private:
	int deckNumber;

	std::vector<std::vector<int>> allCards;
};