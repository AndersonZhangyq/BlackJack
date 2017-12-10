#include "stdafx.h"
#include "Judger.h"
#include "Printer.h"
#include <vector>
#include <iostream>

using namespace std;

void Judger::judgeWinner(Player player, Dealer dealer, int player_id, float times)
{
	if (dealer.isBlackJack())
	{
		cout << "玩家  " << player_id << " 输了！庄家拿到了 BlackJack！" << endl;
		player.afterJudgeSetBet(Lose, times);
		return;
	}
	if (player.isBlackJack())
	{
		cout << "玩家 " << player_id << " 赢了！BlackJack 最大！" << endl;
		player.afterJudgeSetBet(Win, times);
		return;
	}
	int p_b = player.getBest();
	int d_b = dealer.getBest();
	if (p_b > d_b)
	{
		cout << "玩家 " << player_id << " 赢了！手牌总和为：" << p_b;
		player.afterJudgeSetBet(Win, times);
	}
	else if (p_b < d_b)
	{
		cout << "玩家 " << player_id << " 输了！手牌总和为：" << p_b;
		player.afterJudgeSetBet(Lose, times);
	}
	else
	{
		cout << "平局！玩家 " << player_id << " 的手牌总和为：" << p_b;
		player.afterJudgeSetBet(Draw, times);
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

void Judger::judegeBetweenPlayer(Player a, int a_id, Player b, int b_id)
{
	int a_best = a.getBest(), b_best = b.getBest();
	if (a_best > 22 || b_best > 22)
	{
		if (a_best > 22 && b_best > 22)
		{
			// 平局没有赌注变更
			cout << "平局！玩家 " << a_id << " 的手牌总和为：" << a_best << endl
				<< "玩家 " << b_id << " 的手牌总和为：" << b_best << endl;
		}
		else if (a_best > 22)
		{
			cout << "玩家 " << a_id << " 输了！手牌总和为：" << a_best << endl
				<< "玩家 " << b_id << " 赢了！手牌总和为：" << b_best << endl;
			a.afterJudgeSetBet(Lose, 0.5, true, a.getTotalBet());
			b.afterJudgeSetBet(Win, 0.5, true, a.getTotalBet());
			cout << "玩家 " << a_id << " 将 " << a.getTotalBet() * 0.5 << " 给了玩家" << b_id << endl
				<< "Player " << a_id << " has " << a.getLeftBet() << " left" << endl
				<< "Player " << b_id << " has " << b.getLeftBet() << " left" << endl;
		}
		else
		{
			cout << "玩家 " << a_id << " 赢了！手牌总和为：" << a_best << endl
				<< "玩家 " << b_id << " 输了！手牌总和为：" << b_best << endl;
			a.afterJudgeSetBet(Win, 0.5, true, b.getTotalBet());
			b.afterJudgeSetBet(Lose, 0.5, true, b.getTotalBet());
			cout << "玩家 " << b_id << " 将 " << a.getTotalBet() * 0.5 << " 给了玩家" << a_id << endl
				<< "Player " << a_id << " has " << a.getLeftBet() << " left" << endl
				<< "Player " << b_id << " has " << b.getLeftBet() << " left" << endl;
		}
	}
	else
	{
		if (a_best == b_best)
		{
			// 平局没有赌注变更
			cout << "平局！玩家 " << a_id << " 的手牌总和为：" << a_best << endl
				<< "玩家 " << b_id << " 的手牌总和为：" << b_best << endl;
		}
		else if (a_best > b_best)
		{
			cout << "玩家 " << a_id << " 赢了！手牌总和为：" << a_best << endl
				<< "玩家 " << b_id << " 输了！手牌总和为：" << b_best << endl;
			a.afterJudgeSetBet(Win, 0.5, true, b.getTotalBet());
			b.afterJudgeSetBet(Lose, 0.5, true, b.getTotalBet());
			cout << "玩家 " << b_id << " 将 " << a.getTotalBet() * 0.5 << " 给了玩家" << a_id << endl
				<< "Player " << a_id << " has " << a.getLeftBet() << " left" << endl
				<< "Player " << b_id << " has " << b.getLeftBet() << " left" << endl;
		}
		else
		{
			cout << "玩家 " << a_id << " 输了！手牌总和为：" << a_best << endl
				<< "玩家 " << b_id << " 赢了！手牌总和为：" << b_best << endl;
			a.afterJudgeSetBet(Lose, 0.5, true, a.getTotalBet());
			b.afterJudgeSetBet(Win, 0.5, true, a.getTotalBet());
			cout << "玩家 " << a_id << " 将 " << a.getTotalBet() * 0.5 << " 给了玩家" << b_id << endl
				<< "Player " << a_id << " has " << a.getLeftBet() << " left" << endl
				<< "Player " << b_id << " has " << b.getLeftBet() << " left" << endl;
		}
	}
}
