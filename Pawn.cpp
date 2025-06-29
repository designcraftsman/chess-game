#include "Pawn.h"
#include <vector>
#include <string>

using namespace Entities;

Pawn::Pawn(std::string position,std::string pieceType) :Piece(position,pieceType) {

}

std::vector<std::string> Pawn::getPossibleMovements(int idPlayer) {
    std::string current_position = this->position;
    std::vector<std::string> positions;


    char letter = current_position[0];
    char number = current_position[1];

    char forward_2;
    char forward_1;

    if (idPlayer == 1) {
        forward_2 = letter + 2;
        forward_1 = letter + 1;
    }
    else {
        forward_2 = letter - 2;
        forward_1 = letter - 1;
    }
    char attack_left = number - 1;
    char attack_right = number + 1;


    positions.push_back(std::string(1, forward_2) + std::string(1, number));
    positions.push_back(std::string(1, forward_1) + std::string(1, number));
    
    positions.push_back(std::string(1, forward_1) + std::string(1, attack_left));
    positions.push_back(std::string(1, forward_1) + std::string(1, attack_right));
   

    return positions;
}
