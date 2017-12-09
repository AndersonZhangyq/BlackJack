#include "stdafx.h"
#include "Judger.h"
#include "Printer.h"
#include <vector>
#include <iostream>

using namespace std;

void Judger::judgeWinner(Player player, Dealer dealer,int player_id, float times)
{
	if (dealer.isBlackJack())
	{
		cout << "玩家  " << player_id << " 输了！庄家拿到了 BlackJack！" << endl;
		player.endGameSet(Lose, times);
		return;
	}
	if (player.isBlackJack())
	{
		cout << "玩家 " << player_id << " 赢了！BlackJack 最大！" << endl;
		player.endGameSet(Win, times);
		return;
	}
	int p_b = player.getBest();
	int d_b = dealer.getBest();
	if (p_b > d_b)
	{
		cout << "玩家 " << player_id << " 赢了！手牌总和为：" << p_b;
		player.endGameSet(Win, times);
	}else if (p_b < d_b)
	{
		cout << "玩家 " << player_id << " 输了！手牌总和为：" << p_b;
		player.endGameSet(Lose, times);
	}
	else
	{
		cout << "平局！玩家 " << player_id << " 的手牌总和为：" << p_b;
		player.endGameSet(Draw, times);
	}
	cout << "  庄家的手牌总和为：" << d_b << endl;
}

bool Judger::isPlayerBoom(Player player, int player_id)
{
	std::vector<int> total = player.getCardTotal();
	// If the smallest sum is bigger than 21, than boom
	if (total[0] > 22)
	{
		Printer::boom(total[0], player.getHandDescriptionString(), player_id);
		return true;
	}
	return false;
}

bool Judger::isDealerBoom(Dealer dealer)
{
	std::vector<int> total = dealer.getCardTotal();
	// If the smallest sum is bigger than 21, than boom
	if (total[0] > 22)
	{
		Printer::boom(total[0], dealer.getHandDescriptionString(), -1);
		return true;
	}
	return false;
}
