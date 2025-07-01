#include "Bishop.h"

using namespace Entities;

Bishop::Bishop(std::string position, std::string pieceType):Piece(position,pieceType) {
	
}

std::vector<std::string> Bishop::getPossibleMovements(int idPlayer) {
    std::string current_position = this->position;
    std::vector<std::string> positions;

 
    char letter = current_position[0];
    char number = current_position[1];
    
    
    while (letter >= 'A' && number >= '1') {
        positions.push_back(std::string(1, letter) + std::string(1, number));
        letter -= 1;
        number -= 1;
    }

    letter = current_position[0];
    number = current_position[1];

    while (letter >= 'A' && number <= '8') {
        positions.push_back(std::string(1, letter) + std::string(1, number));
        letter -= 1;
        number += 1;
    }

    letter = current_position[0];
    number = current_position[1];
    while (letter <= 'H' && number >= '1') {
        positions.push_back(std::string(1, letter) + std::string(1, number));
        letter += 1;
        number -= 1;
    }

    letter = current_position[0];
    number = current_position[1];
    while (letter <= 'H' &&  number <= '8') {
        positions.push_back(std::string(1, letter) + std::string(1, number));
        letter += 1;
        number += 1;
    }


    return positions;
}