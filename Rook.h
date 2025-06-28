#pragma once
#include "Piece.h"
namespace Entities {

	class Rook: public Piece
	{
	public:
		Rook(std::string position);
		std::vector<std::string> getPossibleMovements(int idPlayer) override;
	};
}
