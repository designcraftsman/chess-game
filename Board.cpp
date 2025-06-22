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
		std::string key ="B"+ std::to_string(i);
		this->pieces[key].assign(pawn.getName());
	}
	for (int j = 1; j < 9; j++) {
		std::string key = "G" + std::to_string(j);
		this->pieces[key].assign(pawn.getName());
	}
	int j = 8;
	for (int i = 1; i < 5; i++) {
		std::string key1 = "A" + std::to_string(i);
		std::string key2 = "A" + std::to_string(j);
		
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
			this->pieces[key2].assign(queen.getName());
		}
		j--;
	}
	for (int i = 1; i < 9; i++) {
		std::string key = "C" + std::to_string(i);
		this->pieces[key]="";
	}
	for (int j = 1; j < 9; j++) {
		std::string key = "D" + std::to_string(j);
		this->pieces[key]="";
	}
	for (int i = 1; i < 9; i++) {
		std::string key = "E" + std::to_string(i);
		this->pieces[key]= "";
	}
	for (int j = 1; j < 9; j++) {
		std::string key = "F" + std::to_string(j);
		this->pieces[key]= "";
	}
	j = 9;
	for (int i = 1; i < 5; i++) {
		std::string key1 = "H" + std::to_string(i);
		std::string key2 = "H" + std::to_string(j);

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
		else {
			Piece king = King();
			Piece queen = Queen();
			this->pieces[key1].assign(king.getName());
			this->pieces[key2].assign(queen.getName());
		}
		j--;
	}

}

std::string Board::printBoard() {
	std::cout << "\n\n\n";
	std::string text;
	std::string message;

	for (const auto& pair : this->pieces) {
		message = "";
		if (pair.second == "")
			message.assign(pair.first + "= EMPTY\t");
		else
			message.assign(pair.first + "=" + pair.second + "\t");

		if (pair.first == "A8" ||
			pair.first == "B8" ||
			pair.first == "C8" ||
			pair.first == "D8" ||
			pair.first == "E8" ||
			pair.first == "F8" ||
			pair.first == "G8") {
			text.assign(text + message + "\n\n");

		}else
			text.assign(text+message);
	}
	return text;
}
