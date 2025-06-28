#pragma once
#include "Piece.h"
namespace Entities {

	class King : public Piece
	{
		public:
			King(std::string position);
			std::vector<std::string> getPossibleMovements(int idPlayer) override;
	};
}
