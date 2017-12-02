#pragma once
#include "Dealer.h"
#include "Person.h"
#include "Player.h"
#include <vector>
#include <string>

using namespace std;

class BlackJackGame {
public:
	BlackJackGame(int playerAmount);
	void playGame();
private:
	Person getWinner();
	bool isEnd();

	Person winner;
	int player_amount;
	Dealer dealer;
	std::vector<Player> players;
	std::vector<bool> isPlayerDone;

};