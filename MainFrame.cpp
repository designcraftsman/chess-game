#include "MainFrame.h"
#include <wx/wx.h>
#include <map>
#include "Pawn.h"
#include "Board.h"
#include "Player.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "King.h"
#include "Queen.h"
#include <string>


MainFrame::MainFrame(const wxString& title):wxFrame(nullptr,wxID_ANY,title){
	this->panel = new wxPanel(this);
	this->isPlayer1Turn = true;
	this->player1 = new Entities::Player(1);
	this->player2 = new Entities::Player(2);
	this->board = new Entities::Board(player1,player2);
	this->createBoard();
}


void MainFrame::OnPieceSelected(wxMouseEvent& evt) {
	if (!this->selectedPiece) {
		this->selectedPiece = int(evt.GetId());
		if (this->isPlayer1Turn) {
			std::vector<std::string> possible_positions = this->player1->selectPiece(this->selectedPiece);
			Entities::Piece* piece = this->player1->findPieceById(this->selectedPiece);
			std::string current_position = piece->getPosition();
			if (dynamic_cast<Entities::Pawn*>(piece)) {
				std::vector<std::string>possible_movements = this->board->PossiblePawnMovements(current_position, possible_positions, this->player2);
				this->possiblePositions = possible_movements;
			}
			else if (dynamic_cast<Entities::Knight*>(piece)) {
				std::vector<std::string>possible_movements = this->board->PossibleKnightMovements(current_position, possible_positions, this->player2);
				this->possiblePositions = possible_movements;
			}
			else if (dynamic_cast<Entities::Bishop*>(piece)) {
				std::vector<std::string>possible_movements = this->board->PossibleBishopMovements(current_position, possible_positions,this->player1 , this->player2);
				this->possiblePositions = possible_movements;
			}
			else if (dynamic_cast<Entities::King*>(piece)) {
				std::vector<std::string>possible_movements = this->board->PossibleKingMovements(current_position, possible_positions,  this->player2);
				this->possiblePositions = possible_movements;
			}else if (dynamic_cast<Entities::Rook*>(piece)) {
				std::vector<std::string>possible_movements = this->board->PossibleRookMovements(current_position, possible_positions, this->player1, this->player2);
				this->possiblePositions = possible_movements;
			}else if (dynamic_cast<Entities::Queen*>(piece)) {
				std::vector<std::string>possible_movements = this->board->PossibleQueenMovements(current_position, possible_positions, this->player1, this->player2);
				this->possiblePositions = possible_movements;
			}
			else {
				return;
			}
			this->createBoard();
		}
		else {
			std::vector<std::string> possible_positions = this->player2->selectPiece(this->selectedPiece);
			Entities::Piece* piece = this->player2->findPieceById(this->selectedPiece);
			std::string current_position = piece->getPosition();
			if (dynamic_cast<Entities::Pawn*>(piece)) {
				std::vector<std::string>possible_movements = this->board->PossiblePawnMovements(current_position, possible_positions, this->player1);
				this->possiblePositions = possible_movements;
			}
			else if (dynamic_cast<Entities::Knight*>(piece)) {
				std::vector<std::string>possible_movements = this->board->PossibleKnightMovements(current_position, possible_positions, this->player1);
				this->possiblePositions = possible_movements;
			}
			else if (dynamic_cast<Entities::Bishop*>(piece)) {
				std::vector<std::string>possible_movements = this->board->PossibleBishopMovements(current_position, possible_positions, this->player2 ,this->player1);
				this->possiblePositions = possible_movements;
			}
			else if (dynamic_cast<Entities::King*>(piece)) {
				std::vector<std::string>possible_movements = this->board->PossibleKingMovements(current_position, possible_positions, this->player1);
				this->possiblePositions = possible_movements;
			}
			else if (dynamic_cast<Entities::Rook*>(piece)) {
				std::vector<std::string>possible_movements = this->board->PossibleRookMovements(current_position, possible_positions, this->player2,this->player1);
				this->possiblePositions = possible_movements;
			}
			else if (dynamic_cast<Entities::Queen*>(piece)) {
				std::vector<std::string>possible_movements = this->board->PossibleQueenMovements(current_position, possible_positions, this->player2, this->player1);
				this->possiblePositions = possible_movements;
			}
			else {
				return;
			}
			this->createBoard();
		}
	}
}

void MainFrame::OnPieceMoved(wxMouseEvent& evt) {
	if (this->selectedPiece) {
		this->movingPosition = this->piecesPositions[int(evt.GetId())];
		int idPiece = int(evt.GetId());
		int targetId = this->board->getPiece(this->movingPosition);
		if (isLegalMove()){
			if (this->isPlayer1Turn) {
				Entities::Piece* piece = this->player1->findPieceById(this->selectedPiece);
				std::string previousPosition = piece->getPosition();
				std::string targetPosition = this->movingPosition;
				int targetId = this->board->getPiece(targetPosition);
				// Determine if it's a valid attack BEFORE moving
				Entities::Piece* targetPiece = this->isPlayer1Turn
					? this->player2->findPieceById(targetId)
					: this->player1->findPieceById(targetId);

				if (targetPiece != nullptr) {
					if (this->isPlayer1Turn)
						this->player2->removePiece(targetId);
					else
						this->player1->removePiece(targetId);
				}

				// Now safely move the piece
				piece->movePiece(targetPosition);

				this->board->updateBoard(this->player1, this->player2, this->possiblePositions, previousPosition, this->movingPosition);
				this->selectedPiece = NULL;
				this->boardPositions.clear();
				this->isPlayer1Turn = false;
				this->panel->DestroyChildren();
				this->possiblePositions.clear();
				this->piecesPositions.clear();
				this->createBoard();
			}
			else {
				Entities::Piece* piece = this->player2->findPieceById(this->selectedPiece);
				std::string previousPosition = piece->getPosition();
				std::string targetPosition = this->movingPosition;
				int targetId = this->board->getPiece(targetPosition);

				// Determine if it's a valid attack BEFORE moving
				Entities::Piece* targetPiece = this->isPlayer1Turn
					? this->player2->findPieceById(targetId)
					: this->player1->findPieceById(targetId);

				if (targetPiece != nullptr) {
					wxLogStatus("Piece removed !");
					if (this->isPlayer1Turn)
						this->player2->removePiece(targetId);
					else
						this->player1->removePiece(targetId);
				}

				// Now safely move the piece
				piece->movePiece(targetPosition);

				this->board->updateBoard(this->player1, this->player2, this->possiblePositions, previousPosition, this->movingPosition);
				this->selectedPiece = NULL;
				this->isPlayer1Turn = true;
				this->boardPositions.clear();
				this->panel->DestroyChildren();
				this->possiblePositions.clear();
				this->piecesPositions.clear();
				this->createBoard();
			}
		}
	}
}



	
bool MainFrame::isLegalMove() {
	for (const auto& i : this->possiblePositions) {
		if (this->movingPosition == i)
			return true;
	}
	return false;
}

bool MainFrame::isAttack(const std::string& position) {
	int pieceId = this->board->getPiece(position);
	if (pieceId == 0) return false;

	if (this->isPlayer1Turn) {
		if (this->player2->findPieceById(pieceId) != nullptr)
			return true;
	}
	else {
		if(this->player1->findPieceById(pieceId) != nullptr)
			return true;
	}
	return false;
}



std::string MainFrame::getPieceType(int idPiece) {
	Entities::Piece* piece = NULL;
	if (this->player1->findPieceById(idPiece)) {
		piece = this->player1->findPieceById(idPiece);

		if (dynamic_cast<Entities::Pawn*>(piece)) {
			return "b_pawn";
		}
		else if (dynamic_cast<Entities::Knight*>(piece)) {
			return "b_knight";
		}
		else if (dynamic_cast<Entities::Bishop*>(piece)) {
			return "b_bishop";
		}
		else if (dynamic_cast<Entities::King*>(piece)) {
			return "b_king";
		}
		else if (dynamic_cast<Entities::Rook*>(piece)) {
			return "b_rook";
		}
		else if (dynamic_cast<Entities::Queen*>(piece)) {
			return "b_queen";
		}
		else {
			return "Undefined";
		}
	}
	if (this->player2->findPieceById(idPiece)) {
		piece = this->player2->findPieceById(idPiece);
		if (dynamic_cast<Entities::Pawn*>(piece)) {
			return "w_pawn";
		}
		else if (dynamic_cast<Entities::Knight*>(piece)) {
			return "w_knight";
		}
		else if (dynamic_cast<Entities::Bishop*>(piece)) {
			return "w_bishop";
		}
		else if (dynamic_cast<Entities::King*>(piece)) {
			return "w_king";
		}
		else if (dynamic_cast<Entities::Rook*>(piece)) {
			return "w_rook";
		}
		else if (dynamic_cast<Entities::Queen*>(piece)) {
			return "w_queen";
		}
		else {
			return "Undefined";
		}
	}

	return "undefined";
}


void MainFrame::createBoard() {
	this->panel->DestroyChildren();

	int index = 40;
	int id;

	std::string itemColor = "white";

	char letter = 'A';
	char number = '1';

	// Create grid sizer for 8x8 board
	wxGridSizer* gridSizer = new wxGridSizer(8, 8, 0, 0);

	for (int i = 1; i <= 64; i++) {
		std::string position = std::string(1, letter) + std::string(1, number);

		if (this->board->getPiece(position) == 0) {
			id = index++;
		}
		else {
			id = this->board->getPiece(position);
		}

		// Use wxDefaultPosition to let sizer handle layout
		wxPanel* itemPanel = new wxPanel(panel, id, wxDefaultPosition, wxSize(70, 70));

		// Your existing color logic (unchanged)
		if (std::find(this->possiblePositions.begin(), this->possiblePositions.end(), position) != this->possiblePositions.end()) {
			itemPanel->SetBackgroundColour(wxColour(135, 206, 250));
			if (itemColor == "green")
				itemColor = (i % 8 == 0) ? "green" : "white";
			else
				itemColor = (i % 8 == 0) ? "white" : "green";
		}
		else if (itemColor == "green") {
			itemPanel->SetBackgroundColour(wxColour(107, 142, 35));
			itemColor = (i % 8 == 0) ? "green" : "white";
		}
		else {
			itemPanel->SetBackgroundColour(wxColour(255, 255, 180));
			itemColor = (i % 8 == 0) ? "white" : "green";
		}

		// Save in maps
		this->boardPositions[position] = itemPanel;
		this->piecesPositions[id] = position;

		// Your existing piece image logic unchanged
		int pieceId = this->board->getPiece(position);
		if (pieceId != 0) {
			std::string pieceType = getPieceType(pieceId);
			std::string imgPath;

			if (pieceType == "b_pawn") {
				imgPath = "pawn.png";
			}
			else if (pieceType == "b_rook") {
				imgPath = "b_Rook.png";
			}
			else if (pieceType == "b_knight") {
				imgPath = "b_Knight.png";
			}
			else if (pieceType == "b_bishop") {
				imgPath = "b_Bishop.png";
			}
			else if (pieceType == "b_king") {
				imgPath = "b_King.png";
			}
			else if (pieceType == "b_queen") {
				imgPath = "b_Queen.png";
			}
			else if (pieceType == "w_rook") {
				imgPath = "w_Rook.png";
			}
			else if (pieceType == "w_pawn") {
				imgPath = "w_Pawn.png";
			}
			else if (pieceType == "w_knight") {
				imgPath = "w_Knight.png";
			}
			else if (pieceType == "w_bishop") {
				imgPath = "w_Bishop.png";
			}
			else if (pieceType == "w_king") {
				imgPath = "w_King.png";
			}
			else if (pieceType == "w_queen") {
				imgPath = "w_Queen.png";
			}

			if (!imgPath.empty() && wxFileExists(imgPath)) {
				wxImage image(imgPath, wxBITMAP_TYPE_PNG);
				if (image.IsOk()) {
					image.Rescale(40, 40);
					wxBitmap bitmap(image);
					wxStaticBitmap* staticImage = new wxStaticBitmap(itemPanel, id, bitmap);
					wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
					sizer->Add(staticImage, 0, wxALL, 5);
					itemPanel->SetSizer(sizer);
				}
			}
		}

		if (this->selectedPiece) {
			itemPanel->Bind(wxEVT_LEFT_DOWN, &MainFrame::OnPieceMoved, this);
		}
		else {
			itemPanel->Bind(wxEVT_LEFT_DOWN, &MainFrame::OnPieceSelected, this);
		}

		number += 1;

		// Add panel to grid sizer instead of positioning manually
		gridSizer->Add(itemPanel, 1, wxEXPAND | wxALL, 0);

		if (i % 8 == 0) {
			letter += 1;
			number = '1';
		}
	}

	// Create a box sizer to center the grid sizer inside the panel
	wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);
	boxSizer->Add(gridSizer, 0, wxALIGN_CENTER | wxALL, 20);

	this->panel->SetSizer(boxSizer);
	this->panel->Layout();
}
