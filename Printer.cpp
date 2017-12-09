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
		cout << "玩家 " << player_id << " 的手牌为 ：" << description << endl
			<< "手牌总数为 " << cardTotal << endl;
	}
}
void Printer::commandHelper()
{
	cout << "你可以选择以下操作：" << endl
		<< Hit << "：Hit,  "
		<< Stand << "：Stand,  "
		<< Deal << "：Deal,  "
		<< Terminate << "：Terminate" << endl;
}

void Printer::removeCardCommandHelper()
{
	cout << "你可以选择以下操作：" << endl
		<< RemoveCard - 4 << "：去掉指定的一张牌,  "
		<< RemoveByNum - 4 << "：去掉指定数字的牌,  "
		<< RemoveByType - 4 << "：去掉指定花色的牌,  " << endl;

}

void Printer::removeCardByType()
{
	cout << "你可以选择以下花色的牌：" << endl
		<< Sqades + 1 << "：黑桃,  "
		<< Hearts + 1 << "：红桃,  "
		<< Clubs + 1 << "：草花,  "
		<< Diamonds + 1 << "：方片,  "
		<< -1 << "：退出当前操作"<< endl;
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

void Printer::removeCard(bool isSuccess, int card_type, int card_num)
{
	if (card_num == -1 && card_type == -1)
		return;
	else if (card_num != -1 && card_type != -1)
	{
		Card card(card_num, Card_type(card_type));
		if (isSuccess)
			cout << card.getStringDescription() << " 已拿出！" << endl;
		else
			cout << card.getStringDescription() << " 不存在！" << endl;
	}
	else if (card_num != -1)
	{
		if (isSuccess)
			cout << "所有 " << Card::getCardNumber(card_num) << " 已拿出！" << endl;
		else
			cout << "没有 " << Card::getCardNumber(card_num) << " 了！" << endl;
	}
	else
	{
		string card_type_name = Card::getType(Card_type(card_type));
		if (isSuccess)
			cout << "所有 " << card_type_name << " 已拿出！" << endl;
		else
			cout << card_type_name << " 不存在！" << endl;
	}
}
