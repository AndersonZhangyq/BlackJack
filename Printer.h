#pragma once
#include <string>
#include "Card.h"


class Printer
{
public:
	static void doubleBet(bool isSuccess, int betLeft, int totalBet);
	static void boom(int cardTotal, std::string description, int player_id);
	static void commandHelper();
	static void removeCardCommandHelper();
	static void removeCardByType();
	static void setBet(bool isSuccess, int bet, int left);
	static void removeCard(bool isSuccess, int card_type = -1, int card_num = -1);
};
