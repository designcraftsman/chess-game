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
	this->panel->Center();
	this->isPlayer1Turn = true;
	this->player1 = new Entities::Player(1);
	this->player2 = new Entities::Player(2);
	this->board = new Entities::Board(player1,player2);
	CreateStatusBar();
	this->UpdateUI();
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
				wxLogStatus("Piece type not found");
				return;
			}
			this->UpdateUI();
			wxLogStatus("possible position 0:" + possible_positions.at(0) + "possible position 1:" + possible_positions.at(1) + "possible position 2:" + possible_positions.at(2) + "possible position 3:" + possible_positions.at(3));
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
				wxLogStatus("Piece type not found");
				return;
			}
			this->UpdateUI();
			wxLogStatus("possible position 0:" + possible_positions.at(0) + "possible position 1:" + possible_positions.at(1) + "possible position 2:" + possible_positions.at(2) + "possible position 3:" + possible_positions.at(3));
		}
	}
}

void MainFrame::OnPieceMoved(wxMouseEvent& evt) {
	if (this->selectedPiece) {
		this->movingPosition = this->boardPositions[int(evt.GetId())];
		int idPiece = int(evt.GetId());
		if (isLegalMove()){
			if (this->isPlayer1Turn) {
				Entities::Piece* piece = this->player1->findPieceById(this->selectedPiece);
				std::string previousPosition = piece->getPosition();
				piece->movePiece(this->movingPosition);
				if (this->isAttack(idPiece)) {
					this->player1->removePiece(idPiece);
				}
				this->board->updateBoard(this->player1, this->player2, this->possiblePositions, previousPosition, this->movingPosition);
				this->selectedPiece = NULL;
				this->boardPositions.clear();
				this->isPlayer1Turn = false;
				this->UpdateUI();
			}
			else {
				Entities::Piece* piece = this->player2->findPieceById(this->selectedPiece);
				std::string previousPosition = piece->getPosition();
				piece->movePiece(this->movingPosition);
				if (this->isAttack(idPiece)) {
					this->player2->removePiece(idPiece);
				}
				this->board->updateBoard(this->player1, this->player2, this->possiblePositions, previousPosition, this->movingPosition);
				this->selectedPiece = NULL;
				this->isPlayer1Turn = true;
				this->boardPositions.clear();
				this->UpdateUI();
			}
		}
		else {
			wxLogStatus("illegal move");
		}
	}

}


void MainFrame::UpdateUI() {

	this->panel->DestroyChildren();  
	this->panel->Update();
	this->panel->Center();
	int i = 40;

	int x = 100;
	int y = 40;

	std::string itemColor = "white";

	for (const auto& pair : this->board->getPieces()) {
		wxPanel* itemPanel = new wxPanel(panel, wxID_ANY, wxPoint(x, y), wxSize(50, 50));
		wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
			
		int id = (pair.second == 0) ? i : pair.second;
		std::string label = pair.first + ((pair.second == 0) ? "= 0\t" : "=" + std::to_string(pair.second) + "\t");
		
		std::string imgPath;

		if (pair.second != 0) {
			std::string pieceType = this->getPieceType(pair.second);
			if (pieceType == "pawn") {
				imgPath = "pawn.png";
			}
		}

		wxBitmap bitmap;
		if (!imgPath.empty() && wxFileExists(imgPath)) {
			wxImage image(imgPath, wxBITMAP_TYPE_PNG);
			if (image.IsOk()) {
				image.Rescale(40, 40);
				bitmap = wxBitmap(image);
			}
		}

		wxStaticBitmap* staticImage = new wxStaticBitmap(itemPanel, id, bitmap);

		if (itemColor == "green") {
			itemPanel->SetBackgroundColour(wxColour(107, 142, 35));
			if (pair.first[1] == '8')
				itemColor = "green";
			else
				itemColor = "white";
		}
		else  {
			itemPanel->SetBackgroundColour(wxColour(255, 255, 255));
			if (pair.first[1] == '8')
				itemColor = "white";
			else
				itemColor = "green";
		}
		

		if (this->selectedPiece) {
			staticImage->Bind(wxEVT_LEFT_DOWN, &MainFrame::OnPieceMoved, this);
		}
		else {
			staticImage->Bind(wxEVT_LEFT_DOWN, &MainFrame::OnPieceSelected, this);
		}

		sizer->Add(staticImage, 0, wxALL, 5);

		itemPanel->SetSizer(sizer);
		this->boardPositions[id] = pair.first;

		if (pair.second == 0) i++;

		x += 50;

		if (pair.first[1] == '8') {
			x = 100;
			y += 50;
		}
	}

}
	
boolean MainFrame::isLegalMove() {
	for (const auto& i : this->possiblePositions) {
		if (this->movingPosition == i)
			return true;
	}
	return false;
}

boolean MainFrame::isAttack(int idPiece) {
	if (isPlayer1Turn)
		return (this->player2->findPieceById(idPiece)) == NULL;
	else
		return this->player1->findPieceById(idPiece) == NULL;
}


std::string MainFrame::getPieceType(int idPiece) {
	Entities::Piece* piece = NULL;
	if (this->player1->findPieceById(idPiece))
		piece = this->player1->findPieceById(idPiece);
	if (this->player2->findPieceById(idPiece))
		piece = this->player2->findPieceById(idPiece);

	if (!piece == NULL) {
		if (dynamic_cast<Entities::Pawn*>(piece)) {
			return "pawn";
		}
		else if (dynamic_cast<Entities::Knight*>(piece)) {
			return "knight";
		}
		else if (dynamic_cast<Entities::Bishop*>(piece)) {
			return "bishop";
		}
		else if (dynamic_cast<Entities::King*>(piece)) {
			return "king";
		}
		else if (dynamic_cast<Entities::Rook*>(piece)) {
			return "rook";
		}
		else if (dynamic_cast<Entities::Queen*>(piece)) {
			return "queen";
		}
		else {
			wxLogStatus("Piece type not found");
			return "Undefined";
		}
	}
	return "undefined";
}