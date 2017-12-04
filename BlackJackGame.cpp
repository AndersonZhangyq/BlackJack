#include "stdafx.h"
#include "BlackJackGame.h"
#include "Printer.h"
#include "Judger.h"
#include <iostream>

using namespace std;

BlackJackGame::BlackJackGame(int playerAmount, int deckAmount)
{
	this->deckAmount = deckAmount;
	deck = Deck(deckAmount);
	player_amount = playerAmount;
	dealer = Dealer(*this);
	for (int i = 0; i < player_amount; i++) {
		Player tmp(*this);
		players.push_back(tmp);
		playerStatus.push_back(Playing);
	}
}

void BlackJackGame::startGame()
{
	if (preCheck() == false)
	{
		cout << "没有玩家可以开始游戏，游戏结束！" << endl;
		return;
	}
	cout << endl << "------ 开始下注 ------" << endl;
	for (int i = 0; i < player_amount; i++) {
		cout << endl;
		do
		{
			Player current_player = players[i];
			cout << "玩家 " << i << "：请下注。你拥有的赌注总数为 " << current_player.getLeftBet() << "." << endl;
			string bet;
			cin >> bet;
			int _bet;
			try
			{
				_bet = stoi(bet);
			}
			catch (exception e)
			{
				cout << "请输入一个数字！" << endl;
				continue;;
			}
			if (current_player.setBet(_bet) == true)
				break;
		} while (true);
	}
	cout << endl << "------ 第一轮发牌开始 ------" << endl;
	Card cardGot = deck.getCard();
	dealer.addCard(cardGot);
	cout << "庄家拿到的牌是：" << cardGot.getStringDescription() << endl;
	for (int i = 0; i < player_amount; ++i)
	{
		cout << endl;
		cardGot = deck.getCard();
		Player current_player = players[i];
		current_player.addCard(cardGot);
		cout << "玩家 " << i << " 拿到的牌为：" << cardGot.getStringDescription() << endl;
	}
	cout << endl << "------ 第二轮发牌开始 ------" << endl;
	for (int i = 0; i < player_amount; ++i)
	{
		cout << endl;
		cardGot = deck.getCard();
		players[i].addCard(cardGot);
		cout << "玩家 " << i << " 拿到的牌为：" << cardGot.getStringDescription() << endl;
		if (players[i].tryDouble())
		{
			cout << "你要加倍赌注吗 ? [y/N]" << endl;
			string wantDouble;
			cin >> wantDouble;
			if (wantDouble == "y")
				players[i].doubleBet();
		}
	}
	playGame();
}

void BlackJackGame::playGame()
{
	for (int i = 0; i < player_amount; i++) {
		//  玩家处于无法继续游戏的状态
		if (playerStatus[i] == Exit)
			continue;
		bool isBoomed = false, chooseTerminate = false, endRound = false;
		cout << endl;
		Player current_player = players[i];
		cout << "------ 现在是玩家 " << i << " 的回合 ------" << endl
			<< "你的赌注为 " << current_player.getTotalBet() << endl;
		do
		{
			cout << "你拿到的牌是：" << current_player.getHandDescriptionString() << endl;
			int opCode;
			do
			{
				Printer::commandHelper();
				string op;
				cin >> op;
				try
				{
					opCode = stoi(op);
				}
				catch (exception e)
				{
					cout << "错误的操作码！请重新输入！" << endl;
					continue;;
				}
				if (1 <= opCode && opCode <= 5)
					break;
				cout << "错误的操作码！请重新输入！" << endl;
			} while (true);
			switch (opCode)
			{
			case Hit:
			{
				Card cardGot = deck.getCard();
				current_player.addCard(cardGot);
				cout << "你拿到的牌为：" << cardGot.getStringDescription() << endl;
				break;
			}
			case Stand:
				endRound = true;
				break;
			case Deal:
				endRound = true;
				break;
			case Terminate:
				chooseTerminate = true;
				playerStatus[i] = Terminated;
				break;
			}
			isBoomed = Judger::isPlayerBoom(current_player, i);
		} while (isBoomed == false && chooseTerminate == false && endRound == false);
		// Theoretically impossible to choose the final one "Playing"
		playerStatus[i] = (isBoomed ? Boom : (endRound ? WaitForJudge : (chooseTerminate ? Terminated : BadStatus)));
		// If BadStatus show, must be terrible error. Termiate the program
		if (playerStatus[i] == BadStatus)
		{
			cout << "A critical error occured! Terminate Program.";
			return;
		}
	}
	endGame();
}

void BlackJackGame::endGame()
{
	bool dealerBoom;
	playToEnd(dealerBoom);
	if (dealerBoom == false)
		cout << endl << "庄家操作结束，庄家的手牌为：" << dealer.getHandDescriptionString() << endl;
	cout << endl << "------ 进入游戏结算 ------" << endl;
	for (int i = 0; i < player_amount; ++i)
	{
		switch (playerStatus[i])
		{
		case Boom:
			cout << "玩家 " << i << " 输了。" << endl;
			players[i].endGameSet(Lose, times);
			break;
		case Terminated:
			cout << "玩家 " << i << " 终止了游戏。" << endl;
			break;
		case WaitForJudge:
			if (dealerBoom)
			{
				cout << "玩家 " << i << " 赢了。" << endl;
				players[i].endGameSet(Win, times);
			}
			else
			{
				Judger::judgeWinner(players[i], dealer, i, times);
			}
			break;
		}
	}
}

void BlackJackGame::playToEnd(bool& dealerBoom)
{
	cout << endl << "------ 现在是庄家的回合 ------" << endl;
	while (dealer.getCardTotal()[0] < 17)
	{
		Card cardGot = deck.getCard();
		dealer.addCard(cardGot);
		cout << "庄家拿到的牌为：" << cardGot.getStringDescription() << endl;
	}
	dealerBoom = Judger::isDealerBoom(dealer);
}

bool BlackJackGame::preCheck()
{
	cout << "------ 检查玩家能否开始游戏 ------" << endl;
	int canPlay = 0;
	for (int i = 0; i < player_amount; i++)
	{
		if (playerStatus[i] == Exit)
		{
			continue;
		}
		if (playerStatus[i] == Terminated)
		{
			cout << "玩家 " << i << " 终止游戏，自动退出游戏。" << endl;
			playerStatus[i] = Exit;
			continue;
		}
		if (players[i].canStartGame() == false)
		{
			playerStatus[i] = Exit;
			cout << "玩家 " << i << " 没有赌注了，自动退出游戏。" << endl;
		}
		else
		{
			canPlay++;
		}
	}
	return canPlay > 0;
}
