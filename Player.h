#pragma once
#include <string>
#include <map>
#include "Piece.h"
namespace Entities {


	class Player
	{
	private:
		int id;
		std::string name;
		std::map<Entities::Piece, int > pieces;

	public:
		void selectPiece(int id);
		void movePiece(int id, std::string selectedPosition);
		bool isPlayerTurn();
	};
}
