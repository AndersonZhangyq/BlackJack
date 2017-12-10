#include "stdafx.h"
#include "Hand.h"
#include <algorithm>

Hand::Hand()
{
	cardTotal = {0};
}

void Hand::addCard(Card card)
{
	cards.push_back(card);
	updateCardTotal(card);
}

std::vector<int> Hand::getCardTotal() const
{
	return cardTotal;
}

std::string Hand::getHandDescriptionString()
{
	std::string handInString = "";
	for (Card card : cards)
	{
		handInString += card.getStringDescription() + "  ";
	}
	return handInString;
}

bool Hand::isBlackJack()
{
	if (cards.size() != 2)
		return false;
	if (std::find(cardTotal.begin(), cardTotal.end(), 22) != cardTotal.end())
		return true;
	return false;
}

int Hand::getBest()
{
	for (std::vector<int>::reverse_iterator i = cardTotal.rbegin(); i != cardTotal.rend(); ++i)
	{
		if (*i <= 22)
			return *i;
	}
	return cardTotal[0];
}

void Hand::reset()
{
	cardTotal.clear();
	cardTotal = {0};
	cards.clear();
}

void Hand::updateCardTotal(Card newCard)
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
	std::sort(cardTotal.begin(), cardTotal.end());
}
