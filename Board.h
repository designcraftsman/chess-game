#pragma once
#include "Player.h"
namespace Entities {

class Board
{
	private:
		int id;
		Entities::Player player1;
		Entities::Player player2;
		std::map<std::string, std::string> pieces;

	public:
		Board();
		std::string printBoard();
};
}

