#include "stdafx.h"
#include "Deck.h"
#include <ctime>
#include "Printer.h"

using namespace std;

Deck::Deck()
{
	srand(time(0));
	deckNumber = 1;
	vector<int> tmp = {
		1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,
		43,44,45,46,47,48,49,50,51,52
	};
	allCards.push_back(tmp);
}

Deck::Deck(int deckNumber)
{
	srand(time(0));
	this->deckNumber = deckNumber;
	vector<int> tmp = {
		1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,
		43,44,45,46,47,48,49,50,51,52
	};
	for (int i = 0; i < deckNumber; i++)
	{
		allCards.push_back(tmp);
	}
}

Card Deck::getCard()
{
	int deck_index = rand() % allCards.size();
	int card_index = rand() % allCards[deck_index].size();
	int card = allCards[deck_index][card_index];
	allCards[deck_index].erase(allCards[deck_index].begin() + card_index);
	if (allCards[deck_index].size() == 0)
	{
		allCards.erase(allCards.begin());
		if (allCards.size() == 0)
			restore();
	}
	return Card((card - 1) / 4 + 1, Card_type((card - 1) % 4));
}

void Deck::restore()
{
	allCards.clear();
	vector<int> tmp = {
		1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,
		43,44,45,46,47,48,49,50,51,52
	};
	for (int i = 0; i < deckNumber; i++)
	{
		allCards.push_back(tmp);
	}
}

void Deck::removeCard(int card_num, int card_type)
{
	if (card_num == -1 && card_type == -1)
		return;
	else if (card_num != -1 && card_type != -1)
		removeOneCard(Card_type(card_type), Card_type(card_num));
	else if (card_num == -1)
		removeCardByType(Card_type(card_type));
	else
		removeCardByNumber(card_num);
}

void Deck::removeOneCard(Card_type card_type, Card_type card_num)
{
	int card = (card_num - 1) * 4 + (int)card_type + 1;
	for (auto i = allCards.begin(); i != allCards.end(); ++i)
	{
		auto card_index = find((*i).begin(), (*i).end(), card);
		if (card_index != (*i).end())
		{
			(*i).erase(card_index);
			Printer::removeCard(true, card_type, card_num);
			return;
		}
	}
	Printer::removeCard(false, card_type, card_num);
	return;
}

void Deck::removeCardByType(Card_type card_type)
{
	int card_type_int = (int)card_type;
	bool isSuccess = false;
	for (auto i = allCards.begin(); i != allCards.end(); ++i)
	{
		for (auto j = (*i).begin(); j != (*i).end();)
		{
			if ((*j - 1) % 4 == card_type_int)
			{
				isSuccess = true;
				j = (*i).erase(j);
			}
			else
			{
				++j;
			}
		}
	}
	Printer::removeCard(isSuccess, card_type);
	return;
}

void Deck::removeCardByNumber(int card_num)
{
	bool isSuccess = false;
	for (auto i = allCards.begin(); i != allCards.end(); ++i)
	{
		for (auto j = (*i).begin(); j != (*i).end();)
		{
			if ((*j - 1) / 4 + 1 == card_num)
			{
				isSuccess = true;
				j = (*i).erase(j);
			}
			else
			{
				if ((*j - 1) / 4 + 1 > card_num)
					break;
				++j;
			}
		}
	}
	Printer::removeCard(isSuccess, -1, card_num);
	return;
}
