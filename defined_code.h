#pragma once

enum PlayerStatus
{
	Playing, Boom,
	// Player stand before boom and is waiting for dealer finish drawing cards
	WaitForJudge,
	Terminated,
	Exit,
	// Theoretically impossible
	BadStatus
};
enum Card_type
{
	Sqades, Hearts, Clubs, Diamonds
};
enum OperationCode
{
	Double, Hit, Stand, Deal, Terminate
};
enum GameResult
{
	Win, Lose, Draw
};