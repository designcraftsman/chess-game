#include "MenuFrame.h"
#include "MainFrame.h"
#include <wx/wx.h>


MenuFrame::MenuFrame(const wxString& title) :wxFrame(nullptr, wxID_ANY, title) {

	this->panel = new wxPanel(this);


	Bind(wxEVT_PAINT, &MenuFrame::OnPaint, this);

	wxButton* playButton = new wxButton(this, 5, "Start",wxDefaultPosition,wxSize(400,120));
	wxButton* optionsButton = new wxButton(this, 6, "Options", wxDefaultPosition, wxSize(400, 120));
	wxButton* exitButton = new wxButton(this, 7, "Exit", wxDefaultPosition, wxSize(400, 120));
	SetBackgroundStyle(wxBG_STYLE_PAINT);

	wxFont font(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_BOLD);

	playButton->SetBackgroundColour(wxColor(44, 118, 49));
	playButton->SetFont(font);
	playButton->SetForegroundColour(wxColor(255, 255, 255));
	optionsButton->SetBackgroundColour(wxColor(44, 118, 49));
	optionsButton->SetFont(font);
	optionsButton->SetForegroundColour(wxColor(255, 255, 255));
	exitButton->SetBackgroundColour(wxColor(44, 118, 49));
	exitButton->SetFont(font);
	exitButton->SetForegroundColour(wxColor(255, 255, 255));
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

void MenuFrame::OnPaint(wxPaintEvent& evt) {
	wxPaintDC dc(this);
	wxBitmap backgroundBitmap("menu-background.jpg", wxBITMAP_TYPE_JPEG);
	wxSize panelSize = GetClientSize();
	if (backgroundBitmap.IsOk())
	{
		wxImage img = backgroundBitmap.ConvertToImage();
		img.Rescale(panelSize.GetWidth(), panelSize.GetHeight(), wxIMAGE_QUALITY_HIGH);
		wxBitmap scaledBitmap(img);
		dc.DrawBitmap(scaledBitmap, 0, 0, false);
	}
}