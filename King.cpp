#include "King.h"

using namespace Entities;

King::King(std::string position) :Piece(position) {

}


std::vector<std::string> King::getPossibleMovements(int idPlayer) {
    std::string current_position = this->position;
    std::vector<std::string> positions;


    char letter = current_position[0];
    char number = current_position[1];


    char up = letter - 1;
    char down = letter + 1;
    char left = number - 1;
    char right = number + 1;

    positions.push_back(letter + std::string(1, left));
    positions.push_back(letter + std::string(1, right));
    positions.push_back(std::string(1, up) + number);
    positions.push_back(std::string(1, down) + number);
    positions.push_back(std::string(1, up) + std::string(1, left));
    positions.push_back(std::string(1, up) + std::string(1, right));
    positions.push_back(std::string(1, down) + std::string(1, left));
    positions.push_back(std::string(1, down) + std::string(1, right));

    return positions;
}