#pragma once
#include "Person.h"
#include "Hand.h"
#include "Bet.h"
#include "Card.h"
#include <string>
#include <vector>


class Player : Person {
public:
	Player();
	Player(std::string _name);
	std::string getHand();
	int getTotalBet();
	bool doubleBet();
	int getLeftBet();
	void addCard(Card card);
	std::vector<int> getCardTotal();
private:
	void recursive_get_card_total(std::vector<int>& total, int curernt_index, int temp_sum);
	std::vector<Card> cards;
	Bet* bet_;
	Hand* hand_;
};
