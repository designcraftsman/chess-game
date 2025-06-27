#pragma once
#include <string>
#include <map>
#include "Piece.h"
#include <vector>
#include <list>

namespace Entities {


	class Player
	{
	protected:
		int id;
		std::string name;
		std::list<Piece*> pieces;
	public:
		Player();
		Player(int id);
		std::list<Piece*> getPieces();
		std::vector<std::string> selectPiece(int id);
		bool isPlayerTurn();
		Piece* findPieceById(int id);
	};
}
