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

	for (const std::string& position : positions) {
		if (this->pieces.find(position) == this->pieces.end()) continue;

		auto pieceValue = this->pieces[position];

		if (pieceValue == 0) {
			if (currentPosition[1] == position[1]) {
				possible_movements.push_back(position);
			}
		}
		else if (adversary->findPieceById(pieceValue)) {
			possible_movements.push_back(position);
		}
	}

	return possible_movements;
}

std::vector<std::string> Board::PossibleKingMovements(std::string currentPosition, std::vector<std::string> positions, Player* adversary) {
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

bool Board::isPieceInCollision(std::string position, std::vector<std::string> collisionPositions) {
	for (const auto& it : collisionPositions) {
		if (it == position)
			return true;
	}
	return false;
}

std::vector<std::string> Board::PossibleBishopMovements(std::string currentPosition, std::vector<std::string> positions, Player* currentPlayer, Player* adversary) {
	std::vector<std::string> possible_movements;
	int id = 100;
	int capture = 0;
	std::map<std::string,std::string> collision;
	std::vector<std::string> collisionPositions;
	
	for (const std::string& position : positions) {
		if (this->pieces.find(position) == this->pieces.end()) continue;

		auto pieceValue = this->pieces[position];

		if (currentPlayer->findPieceById(pieceValue)) {
			if (position[0] > currentPosition[0] && position[1] > currentPosition[1])
				collision[position] = "+1+1";
			if (position[0] < currentPosition[0] && position[1] < currentPosition[1])
				collision[position] = "-1-1";
			if (position[0] > currentPosition[0] && position[1] < currentPosition[1])
				collision[position] = "+1-1";
			if (position[0] < currentPosition[0] && position[1] > currentPosition[1])
				collision[position] = "-1+1";
		}
	}

	for (const auto& it : collision) {
		if (it.second == "+1+1") {
			char letter = it.first[0] + 1;
			char number = it.first[1] + 1 ;
			while (letter <= 'H' && number <= '8') {
				collisionPositions.push_back(std::string(1, letter) + std::string(1, number));
				letter += 1;
				number += 1;
			}
		}if (it.second == "-1-1") {
			char letter = it.first[0] -1;
			char number = it.first[1] -1;
			while (letter >= 'A' && number >= '1') {
				collisionPositions.push_back(std::string(1, letter) + std::string(1, number));
				letter -= 1;
				number -= 1;
			}
		}
		if (it.second == "+1-1") {
			char letter = it.first[0] + 1;
			char number = it.first[1] - 1;
			while (letter <= 'H' && number >= '1') {
				collisionPositions.push_back(std::string(1, letter) + std::string(1, number));
				letter += 1;
				number -= 1;
			}
		}
		if (it.second == "-1+1") {
			char letter = it.first[0] - 1;
			char number = it.first[1] + 1;
			while (letter >= 'A' && number <= '8') {
				collisionPositions.push_back(std::string(1, letter) + std::string(1, number));
				letter -= 1;
				number += 1;
			}
		}
	}

	for (const std::string& position : positions) {
		if (this->pieces.find(position) == this->pieces.end()) continue;

		auto pieceValue = this->pieces[position];

		if (!this->isPieceInCollision(position,collisionPositions)) {
			if (pieceValue == 0) {
				this->pieces[position] = id;
				possible_movements.push_back(position);
				id += 100;
			}
			if (capture <0 && adversary->findPieceById(pieceValue)) {
				capture += 1;
				this->pieces[position] = id;
				possible_movements.push_back(position);
				id += 100;
			}
		}
	}

	return possible_movements;
}


std::vector<std::string> Board::PossibleRookMovements(std::string currentPosition, std::vector<std::string> positions, Player* currentPlayer, Player* adversary) {
	std::vector<std::string> possible_movements;
	int id = 100;
	int capture = 0;
	std::map<std::string, std::string> collision;
	std::vector<std::string> collisionPositions;

	for (const std::string& position : positions) {
		if (this->pieces.find(position) == this->pieces.end()) continue;

		auto pieceValue = this->pieces[position];

		if (currentPlayer->findPieceById(pieceValue)) {
			if (position[0] > currentPosition[0] && position[1] == currentPosition[1])
				collision[position] = "+1and0";
			if (position[0] < currentPosition[0] && position[1] == currentPosition[1])
				collision[position] = "-1and0";
			if (position[0] == currentPosition[0] && position[1] < currentPosition[1])
				collision[position] = "0and-1";
			if (position[0] == currentPosition[0] && position[1] > currentPosition[1])
				collision[position] = "0and+1";
		}
	}

	for (const auto& it : collision) {
		if (it.second == "+1and0") {
			char letter = it.first[0] + 1;
			char number = it.first[1];
			while (letter <= 'H') {
				collisionPositions.push_back(std::string(1, letter) + number);
				letter += 1;
			}
		}if (it.second == "-1and0") {
			char letter = it.first[0] - 1;
			char number = it.first[1];
			while (letter >= 'A') {
				collisionPositions.push_back(std::string(1, letter) +number);
				letter -= 1;
			}
		}
		if (it.second == "0and-1") {
			char letter = it.first[0];
			char number = it.first[1] - 1;
			while ( number >= '1') {
				collisionPositions.push_back(letter + std::string(1, number));
				number -= 1;
			}
		}
		if (it.second == "0and+1") {
			char letter = it.first[0];
			char number = it.first[1] + 1;
			while ( number <= '8') {
				collisionPositions.push_back(letter + std::string(1, number));
				number += 1;
			}
		}
	}

	for (const std::string& position : positions) {
		if (this->pieces.find(position) == this->pieces.end()) continue;
		auto pieceValue = this->pieces[position];

		if (!this->isPieceInCollision(position, collisionPositions)) {
			if (pieceValue == 0) {
				this->pieces[position] = id;
				possible_movements.push_back(position);
				id += 100;
			}
			if (capture < 1 && adversary->findPieceById(pieceValue)) {
				capture += 1;
				this->pieces[position] = id;
				std::string capturePosition = position;
				possible_movements.push_back(position);
				id += 100;
			}
		}
	}

	return possible_movements;
}


std::vector<std::string> Board::PossibleQueenMovements(std::string currentPosition, std::vector<std::string> positions, Player* currentPlayer, Player* adversary) {
	std::vector<std::string> possible_movements;
	int id = 100;
	int capture = 0;
	std::map<std::string, std::string> collision;
	std::vector<std::string> collisionPositions;

	for (const std::string& position : positions) {
		if (this->pieces.find(position) == this->pieces.end()) continue;

		auto pieceValue = this->pieces[position];

		if (currentPlayer->findPieceById(pieceValue)) {
			if (position[0] > currentPosition[0] && position[1] > currentPosition[1])
				collision[position] = "+1+1";
			if (position[0] < currentPosition[0] && position[1] < currentPosition[1])
				collision[position] = "-1-1";
			if (position[0] > currentPosition[0] && position[1] < currentPosition[1])
				collision[position] = "+1-1";
			if (position[0] < currentPosition[0] && position[1] > currentPosition[1])
				collision[position] = "-1+1";
		}
	}

	for (const auto& it : collision) {
		if (it.second == "+1+1") {
			char letter = it.first[0] + 1;
			char number = it.first[1] + 1;
			while (letter <= 'H' && number <= '8') {
				collisionPositions.push_back(std::string(1, letter) + std::string(1, number));
				letter += 1;
				number += 1;
			}
		}if (it.second == "-1-1") {
			char letter = it.first[0] - 1;
			char number = it.first[1] - 1;
			while (letter >= 'A' && number >= '1') {
				collisionPositions.push_back(std::string(1, letter) + std::string(1, number));
				letter -= 1;
				number -= 1;
			}
		}
		if (it.second == "+1-1") {
			char letter = it.first[0] + 1;
			char number = it.first[1] - 1;
			while (letter <= 'H' && number >= '1') {
				collisionPositions.push_back(std::string(1, letter) + std::string(1, number));
				letter += 1;
				number -= 1;
			}
		}
		if (it.second == "-1+1") {
			char letter = it.first[0] - 1;
			char number = it.first[1] + 1;
			while (letter >= 'A' && number <= '8') {
				collisionPositions.push_back(std::string(1, letter) + std::string(1, number));
				letter -= 1;
				number += 1;
			}
		}
	}

	for (const std::string& position : positions) {
		if (this->pieces.find(position) == this->pieces.end()) continue;

		auto pieceValue = this->pieces[position];

		if (currentPlayer->findPieceById(pieceValue)) {
			if (position[0] > currentPosition[0] && position[1] == currentPosition[1])
				collision[position] = "+1and0";
			if (position[0] < currentPosition[0] && position[1] == currentPosition[1])
				collision[position] = "-1and0";
			if (position[0] == currentPosition[0] && position[1] < currentPosition[1])
				collision[position] = "0and-1";
			if (position[0] == currentPosition[0] && position[1] > currentPosition[1])
				collision[position] = "0and+1";
		}
	}

	for (const auto& it : collision) {
		if (it.second == "+1and0") {
			char letter = it.first[0] + 1;
			char number = it.first[1];
			while (letter <= 'H') {
				collisionPositions.push_back(std::string(1, letter) + number);
				letter += 1;
			}
		}if (it.second == "-1and0") {
			char letter = it.first[0] - 1;
			char number = it.first[1];
			while (letter >= 'A') {
				collisionPositions.push_back(std::string(1, letter) + number);
				letter -= 1;
			}
		}
		if (it.second == "0and-1") {
			char letter = it.first[0];
			char number = it.first[1] - 1;
			while (number >= '1') {
				collisionPositions.push_back(letter + std::string(1, number));
				number -= 1;
			}
		}
		if (it.second == "0and+1") {
			char letter = it.first[0];
			char number = it.first[1] + 1;
			while (number <= '8') {
				collisionPositions.push_back(letter + std::string(1, number));
				number += 1;
			}
		}
	}

	for (const std::string& position : positions) {
		if (this->pieces.find(position) == this->pieces.end()) continue;

		auto pieceValue = this->pieces[position];

		if (!this->isPieceInCollision(position, collisionPositions)) {
			if (pieceValue == 0) {
				this->pieces[position] = id;
				possible_movements.push_back(position);
				id += 100;
			}
			if (capture <0 && adversary->findPieceById(pieceValue)) {
				capture += 1;
				this->pieces[position] = id;
				possible_movements.push_back(position);
				id += 100;
			}
		}
	}

	return possible_movements;
}


void Board::updateBoard(Player* player1, Player* player2,
	std::vector<std::string> previousPossiblePositions,
	std::string previousPosition, std::string movingPosition) {

	// 1. Clear all previously marked possible positions EXCEPT the one actually moved to
	for (const auto& pos : previousPossiblePositions) {
		if (pos != movingPosition)
			this->pieces[pos] = 0;
	}

	// 2. Remove previous position of the moved piece (just in case)
	this->pieces[previousPosition] = 0;

	// 3. Reset all board pieces to zero
	for (auto& entry : this->pieces) {
		entry.second = 0;
	}

	// 4. Add all current positions of both players
	for (const auto& p : player1->getPieces()) {
		this->pieces[p->getPosition()] = p->getId();
	}
	for (const auto& p : player2->getPieces()) {
		this->pieces[p->getPosition()] = p->getId();
	}
}



int Board::getPiece(std::string position) {
	return this->pieces[position];
}


