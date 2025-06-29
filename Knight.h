#pragma once
#include "Piece.h"
namespace Entities {

	class Knight : public Piece
	{
	public:
		Knight(std::string position, std::string pieceType);
		std::vector<std::string> getPossibleMovements(int idPlayer) override;
	};
}
