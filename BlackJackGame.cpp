#include "stdafx.h"
#include "BlackJackGame.h"
#include <iostream>

using namespace std;

BlackJackGame::BlackJackGame(int playerAmount)
{
	player_amount = playerAmount;
	for (int i = 0; i < player_amount; i++) {
		players.push_back(Player());
		isPlayerDone.push_back(false);
	}
}

Person BlackJackGame::getWinner()
{
	return winner;
}

bool BlackJackGame::isEnd()
{
	return false;
}

void BlackJackGame::playGame()
{
	while (isEnd()) {
		for (int i = 0; i < player_amount; i++) {
			cout << "Now is player" << i << "'s turn" << endl;
			cout << "The card you got: " << players[i].getHand() << endl;
				<< "Please choose what you want to do." << endl;
		}
	}
}
