#include "stdafx.h"
#include "Player.h"
#include <string>
#include "Printer.h"

using namespace std;

Player::Player() : bet_(new Bet()), hand_(new Hand())
{
}

Player::Player(std::string _name) : Person(_name), bet_(new Bet()), hand_(new Hand())
{
}

string Player::getHand()
{
	string handInString = "";
	for (Card card : cards)
	{
		handInString += card.getStringDescription();
	}
	return handInString;
}

int Player::getTotalBet()
{
	return bet_->getBetInUse();
}

bool Player::doubleBet()
{
	if (bet_->couldDoubleBet())
	{
		bet_->doubleBet();
		Printer::doubleBet(true, getLeftBet(), getTotalBet());
		return true;
	}
	Printer::doubleBet(false, getLeftBet(), getTotalBet());
	return false;
}

int Player::getLeftBet()
{
	return bet_->getLeftBet();
}

void Player::addCard(Card card)
{
	cards.push_back(card);
	updateCardTotal(card);
}

vector<int> Player::getCardTotal()
{
	return cardTotal;
}

void Player::updateCardTotal(Card newCard)
{
	int num = newCard.getNumber();
	if (num != 1)
	{
		int size = cardTotal.size();
		for (int i = 0; i < size; ++i)
		{
			cardTotal[i] += num;
		}
	}
	else
	{
		int size = cardTotal.size();
		for (int i = 0; i < size; ++i)
		{
			int origin_sum = cardTotal[i];
			cardTotal[i] += 1;
			cardTotal.push_back(origin_sum + 11);
		}
	}
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
