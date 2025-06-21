#include "Board.h"
#include <iostream>
#include <string>
#include "Bishop.h";
#include "King.h";
#include "Piece.h";
#include "Queen.h";
#include "Pawn.h";
#include "Rook.h";
#include "Knight.h";
#include <windows.h>




using namespace Entities;


Board::Board() {
	Piece pawn = Pawn();
	for (int i = 1; i < 9; i++) {
		std::string key = "B "+i;
		this->pieces[key].assign(pawn.getName());
	}
	for (int i = 1; i < 9; i++) {
		std::string key = "G" + i;
		this->pieces[key].assign(pawn.getName());
	}
	int j = 9;
	for (int i = 1; i < 4; i++) {
		std::string key1 = "A" + i;
		std::string key2 = "A" + j;
		
		if (i == 1) {
			Piece rook = Rook();
			this->pieces[key1].assign(rook.getName());
			this->pieces[key2].assign(rook.getName());
		}
		else if (i == 2) {
			Piece knight = Knight();
			this->pieces[key1].assign(knight.getName());
			this->pieces[key2].assign(knight.getName());
		}
		else if (i == 3) {
			Piece bishop = Bishop();
			this->pieces[key1].assign(bishop.getName());
			this->pieces[key2].assign(bishop.getName());
		}
		else{
			Piece king = King();
			Piece queen = Queen();
			this->pieces[key1].assign(king.getName());
			this->pieces[key2].assign(king.getName());
		}
	}
}

std::string Board::printBoard() {
	std::cout << "\n\n\n";
	std::string text;

	for (int i = 1; i < 2; i++) {
		std::string key1 = "B";
		std::string message;
		for (const auto& pair : this->pieces) {
			message.assign("Key: " + pair.first + ", Value: " + pair.second + "\n");
			text.assign(text+message);
		}
	}

	return text;
}
