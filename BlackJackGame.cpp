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
			if (_bet <= 0)
			{
				cout << "�����������Ķ�ע��" << endl;
				continue;
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
	setCanJudgeWith();
	cout << endl << "------ ������Ϸ���� ------" << endl;
	for (int i = 0; i < player_amount; ++i)
	{
		cout << endl << "------ ��� " << i << " �Ľ��� ------" << endl;
		string canJudgeWithPlayerId = "";
		for (int j = 0; j < player_amount; ++j)
		{
			if (0 == canJudgeWith[i][j])
				canJudgeWithPlayerId += "��� " + to_string(j) + " ";
		}
		if (canJudgeWithPlayerId != "")
		{
			cout << endl << "�Ƿ���Ҫ��������ҽ��бȽϣ�[y/N]" << endl;
			string needJudge;
			cin >> needJudge;
			if (needJudge == "y")
			{
				cout << "��������Ҫ�Ƚϵ���ҵ�id��" + canJudgeWithPlayerId << endl
					<< "����-1�˳��ò�����" << endl;
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
						cout << "���������֣�" << endl;
						continue;;
					}
					if (player_id == -1)
						break;
					else
					{
						if (canJudgeWithPlayerId.find(" " + id_string + " ") != string::npos)
							break;
					}
					cout << "����� id �ţ����������룡" << endl;
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
				cout << "�ѷ�����������ҽ��бȽ�" << endl;
			}
		}
		else
		{
			cout << "û�пɱȽϵ���ң�" << endl;
		}
		cout << endl << "��ׯ�ұȽ�..." << endl;
		switch (playerStatus[i])
		{
		case Boom:
			cout << "��� " << i << " ���ˡ�" << endl;
			players[i].afterJudgeSetBet(Lose, times);
			break;
		case Terminated:
			cout << "��� " << i << " ��ֹ����Ϸ��" << endl;
			break;
		case WaitForJudge:
			if (dealerBoom)
			{
				cout << "��� " << i << " Ӯ�ˡ�" << endl;
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
	cout << endl << "------ ������ׯ�ҵĻغ� ------" << endl;
	while (dealer.getCardTotal()[0] < 17)
	{
		Card cardGot = deck.getCard();
		dealer.addCard(cardGot);
		cout << "ׯ���õ�����Ϊ��" << cardGot.getStringDescription() << endl;
	}
	dealerBoom = Judger::isDealerBoom(dealer);
}
