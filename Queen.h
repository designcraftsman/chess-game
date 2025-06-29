#pragma once
#include "Piece.h"
namespace Entities {

	class Queen : public Piece
	{
	public:
		Queen(std::string position, std::string pieceType);
		std::vector<std::string> getPossibleMovements(int idPlayer) override;
	};
}
