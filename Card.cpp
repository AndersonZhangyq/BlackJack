#include "stdafx.h"
#include "Card.h"

Card::Card()
{
}

Card::Card(int num, Card_type type)
{
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
		card_type = "∫⁄Ã“";
		break;
	case Hearts:
		card_type = "∫ÏÃ“";
		break;
	case Clubs:
		card_type = "≤›ª®";
		break;
	case Diamonds:
		card_type = "∑Ω∆¨";
		break;
	}
	return card_type;
}

std::string Card::getStringDescription() const
{
	std::string description = getType() + "  ";
	switch (number)
	{
	case 1:
		description += "A";
		break;
	case 11:
		description += "J";
		break;
	case 12:
		description += "Q";
		break;
	case 13:
		description += "K";
		break;
	default:
		description += std::to_string(number);
	}
	return description;
}
