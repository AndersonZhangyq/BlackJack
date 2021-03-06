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
	for (int i = 0; i < player_amount; i++)
	{
		Player tmp(*this);
		players.push_back(tmp);
		playerStatus.push_back(Playing);
	}
	canJudgeWith = vector<vector<int>>(player_amount, vector<int>(player_amount, 0));
}

bool BlackJackGame::preCheck()
{
	canJudgeWith = vector<vector<int>>(player_amount, vector<int>(player_amount, 0));
	deck.restore();
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

void BlackJackGame::preConfig()
{
	cout << endl << "------ 游戏自定设置 ------" << endl;
	string cmd;
	cout << "是否需要去掉指定牌？[y/N]" << endl;
	cin >> cmd;
	if (cmd == "y")
	{
		int opCode;
		do
		{
			Printer::removeCardCommandHelper();
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
			if (1 <= opCode && opCode <= 3)
				break;
			cout << "错误的操作码！请重新输入！" << endl;
		}
		while (true);
		switch (opCode + 5)
		{
		case RemoveCard:
			{
				int i = 0;
				while (true)
				{
					int cardType;
					do
					{
						Printer::removeCardByType();
						string op;
						cin >> op;
						try
						{
							cardType = stoi(op);
						}
						catch (exception e)
						{
							cout << "错误的操作码！请重新输入！" << endl;
							continue;;
						}
						if (-1 == cardType || (1 <= cardType && cardType <= 4))
							break;
						cout << "错误的操作码！请重新输入！" << endl;
					}
					while (true);
					if (cardType == -1)
						break;
					int cardNum;
					do
					{
						cout << "请输入要去掉牌的数字，输入 -1 可退出当前操作：" << endl;
						string cN;
						cin >> cN;
						try
						{
							cardNum = stoi(cN);
						}
						catch (exception e)
						{
							cout << "请输入数字！" << endl;
							continue;;
						}
						if (-1 == cardNum || (1 <= cardNum && cardNum <= 13))
							break;
						cout << "错误的操作码！请重新输入！" << endl;
					}
					while (true);
					if (cardNum == -1)
						break;
					deck.removeCard(cardNum, cardType - 1);
					i++;
					if (i == 2)
						break;
					cout << "是否再拿出一张牌？[y/N]" << endl;
					string op;
					cin >> op;
					if (op != "y")
						break;
				}
				break;
			}
		case RemoveByType:
			{
				int cardType;
				do
				{
					Printer::removeCardByType();
					string op;
					cin >> op;
					try
					{
						cardType = stoi(op);
					}
					catch (exception e)
					{
						cout << "错误的操作码！请重新输入！" << endl;
						continue;;
					}
					if (-1 == opCode || (1 <= opCode && opCode <= 4))
						break;
					cout << "错误的操作码！请重新输入！" << endl;
				}
				while (true);
				if (cardType >= 1 && cardType <= 4)
				{
					deck.removeCard(-1, cardType - 1);
				}
			}
			break;
		case RemoveByNum:
			{
				int cardNum;
				do
				{
					cout << "请输入要去掉牌的数字，输入 -1 可退出当前操作：" << endl;
					string cN;
					cin >> cN;
					try
					{
						cardNum = stoi(cN);
					}
					catch (exception e)
					{
						cout << "请输入数字！" << endl;
						continue;;
					}
					if (-1 == cardNum || (1 <= cardNum && cardNum <= 13))
						break;
					cout << "错误的操作码！请重新输入！" << endl;
				}
				while (true);
				if (cardNum >= 1 && cardNum <= 13)
				{
					deck.removeCard(cardNum, -1);
				}
				break;
			}
		}
	}
	cout << "游戏自定设置已完成！" << endl;
}

void BlackJackGame::setCanJudgeWith()
{
	for (auto i = 0; i < player_amount; ++i)
	{
		canJudgeWith[i][i] = -1;
		if (playerStatus[i] == Terminated || playerStatus[i] == Exit || playerStatus[i] == BadStatus)
			for (int j = 0; j < player_amount; ++j)
			{
				canJudgeWith[j][i] = -1;
			}
	}
}

void BlackJackGame::startGame()
{
	preConfig();
	cout << endl << "------ 开始下注 ------" << endl;
	for (int i = 0; i < player_amount; i++)
	{
		//  玩家处于无法继续游戏的状态
		if (playerStatus[i] == Exit)
			continue;
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
			if (_bet <= 0)
			{
				cout << "请输入大于零的赌注！" << endl;
				continue;
			}
			if (current_player.setBet(_bet) == true)
				break;
		}
		while (true);
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
		//  玩家处于无法继续游戏的状态
		if (playerStatus[i] == Exit)
			continue;
		cout << endl;
		cardGot = deck.getCard();
		players[i].addCard(cardGot);
		cout << "玩家 " << i << " 拿到的牌为：" << cardGot.getStringDescription() << endl;
		if (players[i].tryAddBet())
		{
			cout << "你要加倍赌注吗 ? [y/N]" << endl;
			string wantDouble;
			cin >> wantDouble;
			if (wantDouble == "y")
				players[i].addBet();
		}
	}
	playGame();
}

void BlackJackGame::playGame()
{
	for (int i = 0; i < player_amount; i++)
	{
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
			}
			while (true);
			switch (opCode)
			{
			case AddBet:
				{
					int adds;
					do
					{
						cout << "请输入想要增加的赌注数量：" << endl;
						string add_amount;
						cin >> add_amount;
						try
						{
							adds = stoi(add_amount);
						}
						catch (exception e)
						{
							cout << "请输入数字！" << endl;
							continue;;
						}
						current_player.addBet(adds);
						break;
					}
					while (true);
					break;
				}
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
		}
		while (isBoomed == false && chooseTerminate == false && endRound == false);
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
	setCanJudgeWith();
	cout << endl << "------ 进入游戏结算 ------" << endl;
	for (int i = 0; i < player_amount; ++i)
	{
		cout << endl << "------ 玩家 " << i << " 的结算 ------" << endl;
		string canJudgeWithPlayerId = "";
		for (int j = 0; j < player_amount; ++j)
		{
			if (0 == canJudgeWith[i][j])
				canJudgeWithPlayerId += "玩家 " + to_string(j) + " ";
		}
		if (canJudgeWithPlayerId != "")
		{
			cout << endl << "是否需要和其他玩家进行比较？[y/N]" << endl;
			string needJudge;
			cin >> needJudge;
			if (needJudge == "y")
			{
				cout << "请输入想要比较的玩家的id：" + canJudgeWithPlayerId << endl
					<< "输入-1退出该操作。" << endl;
				int player_id;
				do
				{
					string id_string;
					cin >> id_string;
					try
					{
						player_id = stoi(id_string);
					}
					catch (exception e)
					{
						cout << "请输入数字！" << endl;
						continue;;
					}
					if (player_id == -1)
						break;
					else
					{
						if (canJudgeWithPlayerId.find(" " + id_string + " ") != string::npos)
							break;
					}
					cout << "错误的 id 号！请重新输入！" << endl;
				}
				while (true);
				if (player_id != -1)
				{
					Judger::judegeBetweenPlayer(players[i], i, players[player_id], player_id);
					canJudgeWith[i][player_id] = canJudgeWith[player_id][i] = -1;
				}
			}
			else
			{
				cout << "已放弃和其他玩家进行比较" << endl;
			}
		}
		else
		{
			cout << "没有可比较的玩家！" << endl;
		}
		cout << endl << "与庄家比较..." << endl;
		switch (playerStatus[i])
		{
		case Boom:
			cout << "玩家 " << i << " 输了。" << endl;
			players[i].afterJudgeSetBet(Lose, times);
			break;
		case Terminated:
			cout << "玩家 " << i << " 终止了游戏。" << endl;
			break;
		case WaitForJudge:
			if (dealerBoom)
			{
				cout << "玩家 " << i << " 赢了。" << endl;
				players[i].afterJudgeSetBet(Win, times);
			}
			else
			{
				Judger::judgeWinner(players[i], dealer, i, times);
			}
			break;
		}
	}
	for (auto player : players)
	{
		player.reset();
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
