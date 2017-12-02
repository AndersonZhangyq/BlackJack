#pragma once
#include <string>

enum Card_type
{
	Sqades, Hearts, Clubs, Diamonds
};

class Card
{
public:
	Card();
	Card(int num, Card_type type);
	int getNumber();
	std::string getType();
	std::string getStringDescription();
private:
	int number;
	Card_type type;
};