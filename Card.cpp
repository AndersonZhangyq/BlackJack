#include "stdafx.h"
#include "Card.h"

Card::Card()
{
}

Card::Card(int num, Card_type type)
{
	if (num == 1)
		cardNumber = "A";
	else if (num >= 2 && num <= 10)
		cardNumber = std::to_string(num);
	else
	{
		switch (num)
		{
		case 11:
			cardNumber = "J";
			break;
		case 12:
			cardNumber = "Q";
			break;
		case 13:
			cardNumber = "K";
			break;
		}
	}
	number = num >= 10 ? 10 : num;
	this->type = type;
}

int Card::getNumber() const
{
	return number;
}

std::string Card::getType() const
{
	std::string card_type = "";
	switch (type) {
	case Sqades:
		card_type = "ºÚÌÒ";
		break;
	case Hearts:
		card_type = "ºìÌÒ";
		break;
	case Clubs:
		card_type = "²İ»¨";
		break;
	case Diamonds:
		card_type = "·½Æ¬";
		break;
	}
	return card_type;
}

std::string Card::getStringDescription() const
{
	std::string description = getType() + "  " + cardNumber;
	return description;
}
