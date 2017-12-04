#include "stdafx.h"
#include "Dealer.h"
#include "BlackJackGame.h"

Dealer::Dealer()
{
}

Dealer::Dealer(BlackJackGame game) :hand_(new Hand())
{
	game_ = &game;
}

std::string Dealer::getHandDescriptionString() const
{
	return hand_->getHandDescriptionString();
}

bool Dealer::isBlackJack() const
{
	return hand_->isBlackJack();
}

void Dealer::addCard(Card card) const
{
	hand_->addCard(card);
}

int Dealer::getBest() const
{
	return hand_->getBest();
}

std::vector<int> Dealer::getCardTotal() const
{
	return hand_->getCardTotal();
}

void Dealer::reset()
{
	hand_->reset();
}
