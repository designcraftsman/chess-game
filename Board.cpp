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

Board::Board() {

	Player* player1 = new Player(1);
	Player* player2 = new Player(2);
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