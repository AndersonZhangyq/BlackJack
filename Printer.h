#pragma once
#include <string>


class Printer
{
public:
	static void doubleBet(bool isSuccess, int betLeft, int totalBet);
	static void boom(int cardTotal, std::string description, int player_id);
	static void commandHelper();
	static void setBet(bool isSuccess, int bet, int left);
};
