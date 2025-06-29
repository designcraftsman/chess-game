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
		std::string type;
	public:
		Piece(std::string position,std::string type);
		std::string getName();
		int getId();
		Piece* selectPiece(int id);
		std::string getPosition();
		void movePiece(std::string movingPosition);
		virtual std::vector<std::string> getPossibleMovements(int idPlayer) = 0;
		virtual ~Piece() {}
	};
}

