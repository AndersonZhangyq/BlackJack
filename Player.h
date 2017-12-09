#pragma once
#include "Bet.h"
#include "Hand.h"
#include "Card.h"
#include <string>
#include <vector>

class BlackJackGame;

class Player
{
public:
	Player();
	Player(BlackJackGame game);
	std::string getHandDescriptionString() const;
	int getTotalBet() const;
	bool setBet(int bet) const;
	bool doubleBet() const;
	int getLeftBet() const;
	void addCard(Card card) const;
	std::vector<int> getCardTotal() const;
	bool tryDouble() const;
	bool isBlackJack() const;
	int getBest() const;
	void endGameSet(GameResult result, float times) const;
	bool canStartGame() const;
private:
	// void recursive_get_card_total(std::vector<int>& total, int curernt_index, int temp_sum);
	Bet* bet_;
	Hand* hand_;
	BlackJackGame* game_;
};
