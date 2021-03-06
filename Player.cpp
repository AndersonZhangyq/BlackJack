#include "stdafx.h"
#include "Player.h"
#include "BlackJackGame.h"
#include <string>

using namespace std;

Player::Player()
{
}

Player::Player(BlackJackGame game) : bet_(new Bet()), hand_(new Hand())
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

bool Player::addBet(int adds) const
{
	return bet_->addBet(adds);
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

bool Player::tryAddBet(int adds) const
{
	return bet_->tryAddBet(adds);
}

bool Player::isBlackJack() const
{
	return hand_->isBlackJack();
}

int Player::getBest() const
{
	return hand_->getBest();
}

void Player::afterJudgeSetBet(GameResult result, float tiems, bool isPlayerJudge, int bet_amount) const
{
	bet_->afterJudgeSetBet(result, tiems, isPlayerJudge, bet_amount);
}

bool Player::canStartGame() const
{
	return bet_->canStartGame();
}

void Player::reset()
{
	bet_->resetBet();
	hand_->reset();
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
