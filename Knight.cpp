#include "Knight.h"

using namespace Entities;

Knight::Knight(std::string position,std::string pieceType) :Piece(position,pieceType) {

}


std::vector<std::string> Knight::getPossibleMovements(int idPlayer) {
    std::string current_position = this->position;
    std::vector<std::string> positions;


    char letter = current_position[0];
    char number = current_position[1];

    
    char up_2 = letter - 2;
    char up_1 = letter - 1;
    char down_2 = letter + 2;
    char down_1 = letter + 1;

    char left_2 = number - 2;
    char left_1 = number - 1;
    char right_2 = number + 2;
    char right_1 = number + 1;


    positions.push_back(std::string(1, up_2) + std::string(1, left_1));
    positions.push_back(std::string(1, up_2) + std::string(1, right_1));

    positions.push_back(std::string(1, down_2) + std::string(1, left_1));
    positions.push_back(std::string(1, down_2) + std::string(1, right_1));

    positions.push_back(std::string(1, up_1) + std::string(1, left_2));
    positions.push_back(std::string(1, up_1) + std::string(1, right_2));

    positions.push_back(std::string(1, down_1) + std::string(1, left_2));
    positions.push_back(std::string(1, down_1) + std::string(1, right_2));


    return positions;
}