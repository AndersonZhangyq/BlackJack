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
		game.startGame();
		cout << "������Ϸ�� [y/N]" << endl;
		string continueGame;
		cin >> continueGame;
		if (continueGame != "y")
			break;
	}
	cout << "��Ϸ�Խ������˳�������......" << endl;
	return 0;
}