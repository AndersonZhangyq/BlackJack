#include "stdafx.h"
#include "BlackJackGame.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	int playerNum;
	cout << "���������������" << endl;
	cin >> playerNum;
	BlackJackGame game(playerNum);
	while (true)
	{
		if (game.preCheck() == false)
		{
			cout << "û����ҿ��Կ�ʼ��Ϸ����Ϸ������" << endl;
			break;
		}
		game.startGame();
		cout << "������Ϸ�� [y/N]" << endl;
		string continueGame;
		cin >> continueGame;
		if (continueGame != "y")
			break;
	}
	cout << endl << "��Ϸ�ѽ������˳�������......" << endl;
	return 0;
}
