#include "Rook.h"

using namespace Entities;

Rook::Rook(std::string position):Piece(position) {

}

std::vector<std::string> Rook::getPossibleMovements(int idPlayer) {
    std::string current_position = this->position;
    std::vector<std::string> positions;


    char letter = current_position[0];
    char number = current_position[1];

    letter -= 1;
    while (letter >= 'A') {
        positions.push_back(std::string(1, letter) + number);
        letter -= 1;
    }

    letter = current_position[0];
    letter += 1;
    while (letter <= 'H') {
        positions.push_back(std::string(1, letter) + number);
        letter += 1;
    }

    letter = current_position[0];
    number -= 1;
    while (number >= '1') {
        positions.push_back(letter + std::string(1, number));
        number -= 1;
    }

    number = current_position[1];
    number += 1;
    while (number <= '8') {
        positions.push_back( letter + std::string(1, number));
        number += 1;
    }


    return positions;
}