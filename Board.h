#pragma once
#include "Player.h"
#include <vector>

namespace Entities {

class Board
{
	private:
		int id;
		std::map<std::string, int> pieces;
	public:
		Board();
		Board(Player* player1,Player* player2);
		std::map<std::string, int> getPieces();
		std::string printBoard();
		std::vector<std::string> PossibleMovements(std::string currentPosition,std::vector<std::string> positions,Player* adversary);
		void updateBoard(Player* player1, Player* player2, std::vector<std::string> previousPossiblePositions, std::string previousPosition, std::string movingPosition);
};
}

