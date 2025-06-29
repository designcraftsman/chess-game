#pragma once
#include "Piece.h"
namespace Entities {

	class Pawn : public Piece
	{
	public:
		Pawn(std::string position,std::string pieceType);
		std::vector<std::string> getPossibleMovements(int idPlayer) override;
	};
}
