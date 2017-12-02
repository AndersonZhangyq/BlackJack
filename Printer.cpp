#include "stdafx.h"
#include "Printer.h"
#include <iostream>

using namespace std;

void Printer::doubleBet(bool isSuccess, int betLeft, int totalBet)
{
	if (isSuccess)
	{
		cout << "You have doubled your bet. Now the total bet is "
			<< totalBet << endl << "You have " << betLeft << "left." << endl;
	}else
	{
		cout << "You dont have enouth bet to doubled!. Now the total bet is "
			<< totalBet << endl << "You have " << betLeft << "left." << endl;
	}
}
