#pragma once
#include "Card.h"
#include <vector>

class Hand {
public:
	Hand();
	void addCard(Card card);
	std::vector<int> getCardTotal() const;
	std::string getHandDescriptionString();
	bool isBlackJack();
	int getBest();
	void reset();
private:
	void updateCardTotal(Card newCard);
	std::vector<int> cardTotal;
	std::vector<Card> cards;
};
