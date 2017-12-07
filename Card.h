#pragma once
#include <string>
#include "defined_code.h"


class Card
{
public:
	Card();
	Card(int num, Card_type type);
	int getNumber() const;
	std::string getType() const;
	std::string getStringDescription() const;
private:
	std::string cardNumber;
	int number;
	Card_type type;
};
