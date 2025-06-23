#include "MainFrame.h"
#include <wx/wx.h>
#include "Board.h"
#include "Player.h"


MainFrame::MainFrame(const wxString& title):wxFrame(nullptr,wxID_ANY,title){
	wxPanel* panel = new wxPanel(this);
	
	panel->Center();

	this->player1 = new Entities::Player(1);
	this->player2 = new Entities::Player(2);

	this->board = new Entities::Board(player1,player2);

	int x = 50;
	int y = 50;

	for (const auto& pair : board->getPieces()) {
		if (pair.second == 0) {
			wxStaticText* staticBoard = new wxStaticText(panel, pair.second, pair.first + "= 0\t", wxPoint(x, y), wxSize(40, 40));
			staticBoard->Bind(wxEVT_LEFT_DOWN, &MainFrame::OnPieceSelected, this);
			x += 40;
		}
		else {
			wxStaticText* staticBoard = new wxStaticText(panel, pair.second, pair.first + "=" + std::to_string(pair.second) + "\t", wxPoint(x, y), wxSize(40, 40));
			staticBoard->Bind(wxEVT_LEFT_DOWN, &MainFrame::OnPieceSelected, this);
			x += 40;
		}
		if (pair.first == "A8" ||
			pair.first == "B8" ||
			pair.first == "C8" ||
			pair.first == "D8" ||
			pair.first == "E8" ||
			pair.first == "F8" ||
			pair.first == "G8") {
			x = 50;
			y += 50;
		}
	}
	CreateStatusBar();
}


void MainFrame::OnPieceSelected(wxMouseEvent& evt) {
	std::vector<std::string> possible_positions = this->player1->selectPiece(int(evt.GetId()));
	wxLogStatus("position 1 = " + possible_positions.at(0) + " position 2 = " + possible_positions.at(1) + " position 3 = " + possible_positions.at(2) + " position 4 = " + possible_positions.at(3));
}
