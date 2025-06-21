#pragma once
#include <string>

namespace Entities{

	class  Piece
	{
	protected:
		int id;
		std::string position;
		std::string name;
	
	public:
	
		std::string getName();
	
	};
}

