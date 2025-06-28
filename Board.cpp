#include "Board.h"
#include <iostream>
#include <string>
#include "Bishop.h";
#include "King.h";
#include "Piece.h";
#include "Queen.h";
#include "Pawn.h";
#include "Player.h"
#include "Rook.h";
#include "Knight.h";
#include <windows.h>
#include <list>

using namespace Entities;

Board::Board(Player* player1,Player* player2) {

	std::list<Piece*>::iterator it;
	

	for (auto const& i:player1->getPieces()) {
		this->pieces[i->getPosition()] = i->getId();
	}

	for (auto const& i : player2->getPieces()) {
		this->pieces[i->getPosition()] = i->getId();
	}
	
	for (int i = 1; i < 9; i++) {
		std::string key = "C" + std::to_string(i);
		this->pieces[key]=0;
	}
	for (int j = 1; j < 9; j++) {
		std::string key = "D" + std::to_string(j);
		this->pieces[key]=0;
	}
	for (int i = 1; i < 9; i++) {
		std::string key = "E" + std::to_string(i);
		this->pieces[key]= 0;
	}
	for (int j = 1; j < 9; j++) {
		std::string key = "F" + std::to_string(j);
		this->pieces[key]= 0;
	}
}


std::map<std::string, int> Board::getPieces() {
	return this->pieces;
}


std::vector<std::string> Board::PossiblePawnMovements(std::string currentPosition, std::vector<std::string> positions, Player* adversary) {
	std::vector<std::string> possible_movements;
	int id = 100;

	for (const std::string& position : positions) {
		if (this->pieces.find(position) == this->pieces.end()) continue;

		auto pieceValue = this->pieces[position];

		if (pieceValue == 0) {
			if (currentPosition[1] == position[1]) {
				this->pieces[position] = id;
				possible_movements.push_back(position);
				id += 100;
			}
		}
		else if (adversary->findPieceById(pieceValue)) {
			this->pieces[position] = id;
			possible_movements.push_back(position);
			id += 100;
		}
	}

	return possible_movements;
}

std::vector<std::string> Board::PossibleKnightMovements(std::string currentPosition, std::vector<std::string> positions, Player* adversary) {
	std::vector<std::string> possible_movements;
	int id = 100;

	for (const std::string& position : positions) {
		if (this->pieces.find(position) == this->pieces.end()) continue;

		auto pieceValue = this->pieces[position];

		if (pieceValue == 0) {
			this->pieces[position] = id;
			possible_movements.push_back(position);
			id += 100;
		}
		if (adversary->findPieceById(pieceValue)) {
			this->pieces[position] = id;
			possible_movements.push_back(position);
			id += 100;
		}
	}

	return possible_movements;
}



void Board::updateBoard(Player* player1, Player* player2,std::vector<std::string> previousPossiblePositions ,std::string previousPosition,std::string movingPosition) {
	std::list<Piece*>::iterator it;
	
	for (auto const& i : previousPossiblePositions) {
		if (!(i == movingPosition))
			this->pieces[i] = 0;
	}

	for (auto const& i : player1->getPieces()) {
		this->pieces[i->getPosition()] = i->getId();
	}

	for (auto const& i : player2->getPieces()) {
		this->pieces[i->getPosition()] = i->getId();
	}

	for (auto const& i : this->pieces) {
		if (i.first == previousPosition) {
			this->pieces[i.first] = 0;
		}
	}
}
