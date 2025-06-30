#include "MenuFrame.h"
#include "MainFrame.h"
#include <wx/wx.h>


MenuFrame::MenuFrame(const wxString& title) :wxFrame(nullptr, wxID_ANY, title) {

	this->panel = new wxPanel(this);

	wxButton* playButton = new wxButton(this, 5, "Play Game",wxDefaultPosition,wxSize(400,120));
	wxButton* optionsButton = new wxButton(this, 6, "Options", wxDefaultPosition, wxSize(400, 120));
	wxButton* exitButton = new wxButton(this, 7, "Exit", wxDefaultPosition, wxSize(400, 120));

	wxBoxSizer* buttonSizer = new wxBoxSizer(wxVERTICAL);
	buttonSizer->AddStretchSpacer();
	buttonSizer->Add(playButton, 0, wxALL | wxALIGN_CENTER, 10);
	buttonSizer->Add(optionsButton, 0, wxALL | wxALIGN_CENTER, 10);
	buttonSizer->Add(exitButton, 0, wxALL | wxALIGN_CENTER, 10);
	buttonSizer->AddStretchSpacer();
	SetSizer(buttonSizer);

	playButton->Bind(wxEVT_LEFT_DOWN, &MenuFrame::startGameButton, this);
	
}

void MenuFrame::startGameButton(wxMouseEvent& evt) {
	MainFrame* mainFrame = new MainFrame("Game");
	mainFrame->SetClientSize(900, 600);
	mainFrame->SetBackgroundColour(wxColour(200, 200, 200));
	mainFrame->Center();
	mainFrame->Show();
}