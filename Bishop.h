#pragma once
#include "Piece.h"
namespace Entities {

	class Bishop: public Piece
	{
	public:
		Bishop(std::string position);
		std::vector<std::string> getPossibleMovements(int idPlayer) override;
	};
}
