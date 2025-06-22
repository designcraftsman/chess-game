#pragma once
#include "Player.h"
namespace Entities {

class Board
{
	private:
		int id;
		Entities::Player player1;
		Entities::Player player2;
		std::map<std::string, int> pieces;

	public:
		Board();
		Board(Player* player1,Player* player2);
		std::map<std::string, int> getPieces();
		std::string printBoard();
};
}

