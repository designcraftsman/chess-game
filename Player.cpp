#include "Player.h"
#include "Bishop.h";
#include "King.h";
#include "Piece.h";
#include "Queen.h";
#include "Pawn.h";
#include "Rook.h";
#include <string>
#include "Knight.h";
#include <vector>
#include <list>

using namespace Entities;

Player::Player() {

}

Player::Player(int id) {
	if (id == 1) {

		this->id = 1;

		std::string pieceType = "white";

		for (int i = 1; i < 9; i++) {
			std::string key = "B" + std::to_string(i);
			Piece* pawn = new Pawn(key,pieceType);
			pieces.push_back(pawn);
		}
		int j = 8;
		for (int i = 1; i < 5; i++) {
			std::string key1 = "A" + std::to_string(i);
			std::string key2 = "A" + std::to_string(j);

			if (i == 1) {
				Piece* rook1 = new Rook(key1, pieceType);
				Piece* rook2 = new Rook(key2, pieceType);
				pieces.push_back(rook1);
				pieces.push_back(rook2);
			}
			else if (i == 2) {
				Piece* knight1 = new Knight(key1, pieceType);
				Piece* knight2 = new Knight(key2, pieceType);
				pieces.push_back(knight1);
				pieces.push_back(knight2);
			}
			else if (i == 3) {
				Piece* bishop1 = new Bishop(key1, pieceType);
				Piece* bishop2 = new Bishop(key2, pieceType);
				pieces.push_back(bishop1);
				pieces.push_back(bishop2);
			}
			else {
				Piece* king = new King(key1, pieceType);
				Piece* queen = new Queen(key2, pieceType);
				pieces.push_back(king);
				pieces.push_back(queen);
			}
			j--;
		}
	}
	if(id == 2){
		this->id = 2;
		std::string pieceType = "black";
		for (int i = 1; i < 9; i++) {
			std::string key = "G" + std::to_string(i);
			Piece* pawn = new Pawn(key, pieceType);
			pieces.push_back(pawn);
		}
		int j = 8;
		for (int i = 1; i < 5; i++) {
			std::string key1 = "H" + std::to_string(i);
			std::string key2 = "H" + std::to_string(j);

			if (i == 1) {
				Piece* rook1 = new Rook(key1, pieceType);
				Piece* rook2 = new Rook(key2, pieceType);
				pieces.push_back(rook1);
				pieces.push_back(rook2);
			}
			else if (i == 2) {
				Piece* knight1 = new Knight(key1, pieceType);
				Piece* knight2 = new Knight(key2, pieceType);
				pieces.push_back(knight1);
				pieces.push_back(knight2);
			}
			else if (i == 3) {
				Piece* bishop1 = new Bishop(key1, pieceType);
				Piece* bishop2 = new Bishop(key2, pieceType);
				pieces.push_back(bishop1);
				pieces.push_back(bishop2);
			}
			else {
				Piece* king = new King(key1, pieceType);
				Piece* queen = new Queen(key2, pieceType);
				pieces.push_back(king);
				pieces.push_back(queen);
			}
			j--;
		}
	}
}

std::list<Piece*> Player::getPieces() {
	return this->pieces;
}

Piece* Player::findPieceById(int id) {
	for (const auto& it : this->pieces) {
		if (it->getId() == id)
			return it;
	}
	return NULL;
}


std::vector<std::string> Player::selectPiece(int id) {
	Piece* piece = this->findPieceById(id);
	std::vector<std::string> positions = piece->getPossibleMovements(this->id);
	return positions;
}


void Player::removePiece(int idPiece) {
	for (auto it = this->pieces.begin(); it != this->pieces.end(); ++it) {
		if ((*it)->getId() == idPiece) {
			this->pieces.erase(it);
			break; 
		}
	}
}


