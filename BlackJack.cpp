#include "stdafx.h"
#include "BlackJackGame.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	int playerNum;
	cout << "请输入玩家总数：" << endl;
	cin >> playerNum;
	BlackJackGame game(playerNum);
	while (true)
	{
		game.startGame();
		cout << "继续游戏吗？ [y/N]" << endl;
		string continueGame;
		cin >> continueGame;
		if (continueGame != "y")
			break;
	}
	cout << "游戏以结束，退出程序中......" << endl;
	return 0;
}