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
		if (game.preCheck() == false)
		{
			cout << "没有玩家可以开始游戏，游戏结束！" << endl;
			break;
		}
		game.startGame();
		cout << "继续游戏吗？ [y/N]" << endl;
		string continueGame;
		cin >> continueGame;
		if (continueGame != "y")
			break;
	}
	cout << endl << "游戏已结束，退出程序中......" << endl;
	return 0;
}
