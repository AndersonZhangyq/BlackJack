#include "stdafx.h"
#include "Printer.h"
#include <iostream>
#include "defined_code.h"

using namespace std;

void Printer::doubleBet(bool isSuccess, int betLeft, int totalBet)
{
	if (isSuccess)
	{
		cout << "你已经加倍赌注. 当前赌注为 " << totalBet << endl
			<< "你还剩余的赌注为 " << betLeft << endl;
	}
	else
	{
		cout << "你没有足够的赌注来加倍！当前赌注为 " << totalBet << endl
			<< "你还剩余的赌注为 " << betLeft << endl;
	}
}

void Printer::boom(int cardTotal, string description, int player_id)
{
	cout << endl;
	cout << "BOOM!!!!" << endl;
	if (player_id == -1)
		cout << "庄家的手牌为：" << description << endl
			<< "手牌总数为 " << cardTotal << endl;
	else
	{
		cout << "玩家 " << player_id << " 的手牌为 : " << description << endl
			<< "手牌总数为 " << cardTotal << endl;
	}
}
void Printer::commandHelper()
{
	cout << "你可以选择以下操作: " << endl
		<< Hit << ": Hit,  "
		<< Stand << ": Stand,  "
		<< Deal << ": Deal,  "
		<< Terminate << ": Terminate" << endl;
}

void Printer::setBet(bool isSuccess, int bet, int left)
{
	if (isSuccess)
	{
		cout << "成功下注. 赌注总数为 " << bet << endl
			<< "剩余的赌注为 " << left << endl;
	}
	else
	{
		cout << "你没有足够的赌注来下注！" << endl
			<< "剩余的赌注为 " << left << endl;
	}
}
