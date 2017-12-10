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
}

bool BlackJackGame::preCheck()
{
	cout << "------ �������ܷ�ʼ��Ϸ ------" << endl;
	int canPlay = 0;
	for (int i = 0; i < player_amount; i++)
	{
		if (playerStatus[i] == Exit)
		{
			continue;
		}
		if (playerStatus[i] == Terminated)
		{
			cout << "��� " << i << " ��ֹ��Ϸ���Զ��˳���Ϸ��" << endl;
			playerStatus[i] = Exit;
			continue;
		}
		if (players[i].canStartGame() == false)
		{
			playerStatus[i] = Exit;
			cout << "��� " << i << " û�ж�ע�ˣ��Զ��˳���Ϸ��" << endl;
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
	cout << endl << "------ ��Ϸ�Զ����� ------" << endl;
	string cmd;
	cout << "�Ƿ���Ҫȥ��ָ���ƣ�[y/N]" << endl;
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
				cout << "����Ĳ����룡���������룡" << endl;
				continue;;
			}
			if (1 <= opCode && opCode <= 3)
				break;
			cout << "����Ĳ����룡���������룡" << endl;
		}
		while (true);
		switch (opCode + 4)
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
							cout << "����Ĳ����룡���������룡" << endl;
							continue;;
						}
						if (-1 == cardType || (1 <= cardType && cardType <= 4))
							break;
						cout << "����Ĳ����룡���������룡" << endl;
					}
					while (true);
					if (cardType == -1)
						break;
					int cardNum;
					do
					{
						cout << "������Ҫȥ���Ƶ����֣����� -1 ���˳���ǰ������" << endl;
						string cN;
						cin >> cN;
						try
						{
							cardNum = stoi(cN);
						}
						catch (exception e)
						{
							cout << "���������֣�" << endl;
							continue;;
						}
						if (-1 == cardNum || (1 <= cardNum && cardNum <= 13))
							break;
						cout << "����Ĳ����룡���������룡" << endl;
					}
					while (true);
					if (cardNum == -1)
						break;
					deck.removeCard(cardNum, cardType - 1);
					i++;
					if (i == 2)
						break;
					cout << "�Ƿ����ó�һ���ƣ�[y/N]" << endl;
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
						cout << "����Ĳ����룡���������룡" << endl;
						continue;;
					}
					if (-1 == opCode || (1 <= opCode && opCode <= 4))
						break;
					cout << "����Ĳ����룡���������룡" << endl;
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
					cout << "������Ҫȥ���Ƶ����֣����� -1 ���˳���ǰ������" << endl;
					string cN;
					cin >> cN;
					try
					{
						cardNum = stoi(cN);
					}
					catch (exception e)
					{
						cout << "���������֣�" << endl;
						continue;;
					}
					if (-1 == cardNum || (1 <= cardNum && cardNum <= 13))
						break;
					cout << "����Ĳ����룡���������룡" << endl;
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
	cout << "��Ϸ�Զ���������ɣ�" << endl;
}

void BlackJackGame::startGame()
{
	preConfig();
	cout << endl << "------ ��ʼ��ע ------" << endl;
	for (int i = 0; i < player_amount; i++)
	{
		//  ��Ҵ����޷�������Ϸ��״̬
		if (playerStatus[i] == Exit)
			continue;
		cout << endl;
		do
		{
			Player current_player = players[i];
			cout << "��� " << i << "������ע����ӵ�еĶ�ע����Ϊ " << current_player.getLeftBet() << "." << endl;
			string bet;
			cin >> bet;
			int _bet;
			try
			{
				_bet = stoi(bet);
			}
			catch (exception e)
			{
				cout << "������һ�����֣�" << endl;
				continue;;
			}
			if (current_player.setBet(_bet) == true)
				break;
		}
		while (true);
	}
	cout << endl << "------ ��һ�ַ��ƿ�ʼ ------" << endl;
	Card cardGot = deck.getCard();
	dealer.addCard(cardGot);
	cout << "ׯ���õ������ǣ�" << cardGot.getStringDescription() << endl;
	for (int i = 0; i < player_amount; ++i)
	{
		cout << endl;
		cardGot = deck.getCard();
		Player current_player = players[i];
		current_player.addCard(cardGot);
		cout << "��� " << i << " �õ�����Ϊ��" << cardGot.getStringDescription() << endl;
	}
	cout << endl << "------ �ڶ��ַ��ƿ�ʼ ------" << endl;
	for (int i = 0; i < player_amount; ++i)
	{
		//  ��Ҵ����޷�������Ϸ��״̬
		if (playerStatus[i] == Exit)
			continue;
		cout << endl;
		cardGot = deck.getCard();
		players[i].addCard(cardGot);
		cout << "��� " << i << " �õ�����Ϊ��" << cardGot.getStringDescription() << endl;
		if (players[i].tryAddBet())
		{
			cout << "��Ҫ�ӱ���ע�� ? [y/N]" << endl;
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
		//  ��Ҵ����޷�������Ϸ��״̬
		if (playerStatus[i] == Exit)
			continue;
		bool isBoomed = false, chooseTerminate = false, endRound = false;
		cout << endl;
		Player current_player = players[i];
		cout << "------ ��������� " << i << " �Ļغ� ------" << endl
			<< "��Ķ�עΪ " << current_player.getTotalBet() << endl;
		do
		{
			cout << "���õ������ǣ�" << current_player.getHandDescriptionString() << endl;
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
					cout << "����Ĳ����룡���������룡" << endl;
					continue;;
				}
				if (1 <= opCode && opCode <= 5)
					break;
				cout << "����Ĳ����룡���������룡" << endl;
			}
			while (true);
			switch (opCode)
			{
			case AddBet:
				{
					int adds;
					do
					{
						cout << "��������Ҫ���ӵĶ�ע������" << endl;
						string add_amount;
						cin >> add_amount;
						try
						{
							adds = stoi(add_amount);
						}
						catch (exception e)
						{
							cout << "���������֣�" << endl;
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
					cout << "���õ�����Ϊ��" << cardGot.getStringDescription() << endl;
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
		cout << endl << "ׯ�Ҳ���������ׯ�ҵ�����Ϊ��" << dealer.getHandDescriptionString() << endl;
	cout << endl << "------ ������Ϸ���� ------" << endl;
	for (int i = 0; i < player_amount; ++i)
	{
		switch (playerStatus[i])
		{
		case Boom:
			cout << "��� " << i << " ���ˡ�" << endl;
			players[i].endGameSet(Lose, times);
			break;
		case Terminated:
			cout << "��� " << i << " ��ֹ����Ϸ��" << endl;
			break;
		case WaitForJudge:
			if (dealerBoom)
			{
				cout << "��� " << i << " Ӯ�ˡ�" << endl;
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
	cout << endl << "------ ������ׯ�ҵĻغ� ------" << endl;
	while (dealer.getCardTotal()[0] < 17)
	{
		Card cardGot = deck.getCard();
		dealer.addCard(cardGot);
		cout << "ׯ���õ�����Ϊ��" << cardGot.getStringDescription() << endl;
	}
	dealerBoom = Judger::isDealerBoom(dealer);
}
