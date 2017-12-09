#pragma once
#include "Card.h"
#include <vector>

class Deck
{
public:
	Deck();
	Deck(int deckNumber);
	Card getCard();
	void restore();
	void removeCard(int card_num = -1, int card_type = -1);
private:
	void removeOneCard(Card_type card_type, Card_type card_num);
	void removeCardByType(Card_type card_type);
	void removeCardByNumber(int card_num);
	int deckNumber;

	std::vector<std::vector<int>> allCards;
};
