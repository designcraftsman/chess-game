#pragma once
#include "Piece.h"
namespace Entities {

	class Queen : public Piece
	{
	public:
		Queen(std::string position);
		std::vector<std::string> getPossibleMovements(int idPlayer) override;
	};
}
