#include "stdafx.h"
#include "Player.h"
#include "BlackJackGame.h"
#include <string>

using namespace std;

Player::Player()
{
}

Player::Player(BlackJackGame game) :bet_(new Bet()), hand_(new Hand())
{
	game_ = &game;
}

string Player::getHandDescriptionString() const
{
	return hand_->getHandDescriptionString();
}

int Player::getTotalBet() const
{
	return bet_->getBetInUse();
}

bool Player::setBet(int bet) const
{
	return bet_->setBet(bet);
}

bool Player::doubleBet() const
{	
	return bet_->doubleBet();
}

int Player::getLeftBet() const
{
	return bet_->getLeftBet();
}

void Player::addCard(Card card) const
{
	hand_->addCard(card);
}

vector<int> Player::getCardTotal() const
{
	return hand_->getCardTotal();
}

bool Player::tryDouble() const
{
	return bet_->tryDouble();
}

bool Player::isBlackJack() const
{
	return hand_->isBlackJack();
}

int Player::getBest() const
{
	return hand_->getBest();
}

void Player::endGameSet(GameResult result,float tiems) const
{
	bet_->endGameSet(result, tiems);
	hand_->reset();
}

bool Player::canStartGame() const
{
	return bet_->canStartGame();
}

/*void Player::recursive_get_card_total(std::vector<int>& total, int current_index, int temp_sum)
{
	if (current_index == cards.size())
	{
		total.push_back(temp_sum);
		return;
	}
	Card current_card = cards[current_index];
	int num = current_card.getNumber();
	if (num != 1)
	{
		recursive_get_card_total(total, current_index + 1, temp_sum + num);
	}
	else
	{
		recursive_get_card_total(total, current_index + 1, temp_sum + 1);
		recursive_get_card_total(total, current_index + 1, temp_sum + 11);
	}
}*/
