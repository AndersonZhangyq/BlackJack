#pragma once
#include "Player.h"
#include "Dealer.h"

class Judger
{
public:
	static void judgeWinner(Player player, Dealer dealer, int player_id, float times);
	static bool isPlayerBoom(Player player, int player_id);
	static bool isDealerBoom(Dealer dealer);
	static void judegeBetweenPlayer(Player a,int a_id, Player b, int b_id);
};
