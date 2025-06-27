#include "MainFrame.h"
#include <wx/wx.h>
#include <map>
#include "Board.h"
#include "Player.h"
#include <string>


MainFrame::MainFrame(const wxString& title):wxFrame(nullptr,wxID_ANY,title){
	this->panel = new wxPanel(this);
	this->panel->Center();
	this->player1 = new Entities::Player(1);
	this->player2 = new Entities::Player(2);
	this->board = new Entities::Board(player1,player2);
	CreateStatusBar();
	this->UpdateUI();
}


void MainFrame::OnPieceSelected(wxMouseEvent& evt) {
	if (!this->selectedPiece) {
		this->selectedPiece = int(evt.GetId());
		std::vector<std::string> possible_positions = this->player1->selectPiece(this->selectedPiece);
		Entities::Piece* piece = this->player1->findPieceById(this->selectedPiece);
		std::string current_position = piece->getPosition();
		std::vector<std::string>possible_movements = this->board->PossibleMovements(current_position, possible_positions, this->player2);
		this->possiblePositions = possible_movements;
		wxLogStatus("position 1 = " + possible_positions.at(0) + " position 2 = " + possible_positions.at(1) + " position 3 = " + possible_positions.at(2) + " position 4 = " + possible_positions.at(3));
		this->UpdateUI();
	}
}

void MainFrame::OnPieceMoved(wxMouseEvent& evt) {
	if (this->selectedPiece) {
		this->movingPosition = this->boardPositions[int(evt.GetId())];
		Entities::Piece* piece = this->player1->findPieceById(this->selectedPiece);
		std::string previousPosition = piece->getPosition();
		piece->movePiece(this->movingPosition);
		this->board->updateBoard(this->player1, this->player2,this->possiblePositions,previousPosition,this->movingPosition);
		wxLogStatus("Selected Position is :" + this->boardPositions[int(evt.GetId())] + "Moving piece: " + previousPosition + " to: " + this->movingPosition);
		this->selectedPiece = NULL;
		this->UpdateUI();
	}
}


void MainFrame::UpdateUI() {

	this->panel->DestroyChildren();  
	this->panel->Update();
	int i = 40;

	int x = 50;
	int y = 50;

	for (const auto& pair : this->board->getPieces()) {
		wxStaticText* staticBoard = nullptr;
		int id = (pair.second == 0) ? i : pair.second;
		std::string label = pair.first + ((pair.second == 0) ? "= 0\t" : "=" + std::to_string(pair.second) + "\t");

		staticBoard = new wxStaticText(panel, id, label, wxPoint(x, y), wxSize(40, 40));

		if (this->selectedPiece) {
			staticBoard->Bind(wxEVT_LEFT_DOWN, &MainFrame::OnPieceMoved, this);
		}
		else {
			staticBoard->Bind(wxEVT_LEFT_DOWN, &MainFrame::OnPieceSelected, this);
		}

		this->boardPositions[id] = pair.first;

		if (pair.second == 0) i++;

		x += 40;

		if (pair.first == "A8" || pair.first == "B8" || pair.first == "C8" ||
			pair.first == "D8" || pair.first == "E8" || pair.first == "F8" || pair.first == "G8") {
			x = 50;
			y += 50;
		}
	}

}
