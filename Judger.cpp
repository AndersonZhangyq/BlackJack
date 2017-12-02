#include "stdafx.h"
#include "Judger.h"
#include <vector>
#include <algorithm>

bool Judger::isBoom(Player player)
{
	std::vector<int> total = player.getCardTotal();
	std::sort(total.begin(), total.end());
	// If the smallest sum is bigger than 21, than boom
	return total[0] > 21;
}
