#pragma once
#include "Person.h"
#include "Hand.h"
#include "Bet.h"
#include <string>

class Dealer : Person {
public:
	Dealer();
	Dealer(std::string _name);
private:
	Bet* bet_;
	Hand* hand_;
};
