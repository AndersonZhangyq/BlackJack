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
	bool addBet(int adds = -1) const;
	int getLeftBet() const;
	void addCard(Card card) const;
	std::vector<int> getCardTotal() const;
	bool tryAddBet(int adds = -1) const;
	bool isBlackJack() const;
	int getBest() const;
	void afterJudgeSetBet(GameResult result, float times, bool isPlayerJudge = false, int bet_amount = -1) const;
	bool canStartGame() const;
	void reset();
private:
	// void recursive_get_card_total(std::vector<int>& total, int curernt_index, int temp_sum);
	Bet* bet_;
	Hand* hand_;
	BlackJackGame* game_;
};
