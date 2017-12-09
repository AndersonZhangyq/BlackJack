#include "stdafx.h"
#include "Card.h"

Card::Card()
{
}

Card::Card(int num, Card_type type)
{
	cardNumber = getCardNumber(num);
	number = num >= 10 ? 10 : num;
	this->type = type;
}

std::string Card::getCardNumber(int num)
{
	if (num == 1)
		return "A";
	else if (num >= 2 && num <= 10)
		return std::to_string(num);
	else
	{
		switch (num)
		{
		case 11:
			return "J";
			break;
		case 12:
			return "Q";
			break;
		case 13:
			return "K";
			break;
		}
	}
}

int Card::getNumber() const
{
	return number;
}

std::string Card::getType(Card_type type)
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

std::string Card::getType() const
{
	return getType(type);
}
