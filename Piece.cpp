#include "Piece.h"
#include <vector>
#include <string>

using namespace Entities;

static int ID_INCREMENT = 2;

Piece::Piece(std::string position, std::string pieceType) {
	this->id = ID_INCREMENT;
	ID_INCREMENT++;
	this->position.assign(position);
	this->type.assign(pieceType);
}

std::string Piece::getName() {
	return this->name;
}

int Piece::getId() {
	return this->id;
}

std::string Piece::getPosition() {
	return this->position;
}

void Piece::movePiece(std::string movingPosition) {
	this->position = movingPosition;
}







