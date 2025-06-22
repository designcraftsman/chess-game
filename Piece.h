#pragma once
#include <string>
#include <vector>

namespace Entities{

	class  Piece
	{
	protected:
		int id;
		std::string position;
		std::string name;
	
	public:
		Piece(std::string position);
		std::string getName();
		int getId();
		Piece* selectPiece(int id);
		std::string getPosition();
		virtual std::vector<std::string> getPossibleMovements();
	};
}

