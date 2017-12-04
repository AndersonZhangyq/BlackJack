#pragma once
#include "Dealer.h"
#include "Player.h"
#include "Deck.h"
#include <vector>

using namespace std;

class BlackJackGame {
public:
	BlackJackGame(int playerAmount, int deckAmount = 1);
	void playGame();
	void startGame();
	void endGame();
	void playToEnd(bool& dealerBoom);
	bool preCheck();
private:

	int deckAmount;
	int player_amount;
	Dealer dealer;
	std::vector<Player> players;
	std::vector<PlayerStatus> playerStatus;
	Deck deck;
	float times = 1.5;
};