#include "MainFrame.h"
#include <wx/wx.h>
#include "Board.h"

MainFrame::MainFrame(const wxString& title):wxFrame(nullptr,wxID_ANY,title){
	wxPanel* panel = new wxPanel(this);
	
	Entities::Board* board = new Entities::Board();
	std::string stringBoard = board->printBoard();
	wxStaticText* staticBoard = new wxStaticText(panel, wxID_ANY,stringBoard, wxPoint(50, 50));
}
