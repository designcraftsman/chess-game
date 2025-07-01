#include "MenuFrame.h"
#include "MainFrame.h"
#include "OptionsFrame.h"
#include <wx/wx.h>


MenuFrame::MenuFrame(const wxString& title) :wxFrame(nullptr, wxID_ANY, title) {

	this->panel = new wxPanel(this);


	panel->Bind(wxEVT_PAINT, &MenuFrame::OnPaint, this);


	wxButton* playButton = new wxButton(panel, 5, "Start", wxDefaultPosition, wxSize(400, 120), wxBORDER_NONE);
	wxButton* optionsButton = new wxButton(panel, 6, "Options", wxDefaultPosition, wxSize(400, 120), wxBORDER_NONE);
	wxButton* exitButton = new wxButton(panel, 7, "Exit", wxDefaultPosition, wxSize(400, 120), wxBORDER_NONE);


					
	panel->SetBackgroundStyle(wxBG_STYLE_PAINT);

	wxFont font(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_BOLD);

	playButton->SetBackgroundColour(wxColor(181, 136, 99));
	playButton->SetFont(font);
	playButton->SetForegroundColour(wxColor(255, 255, 255));
	optionsButton->SetBackgroundColour(wxColor(181, 136, 99));
	optionsButton->SetFont(font);
	optionsButton->SetForegroundColour(wxColor(255, 255, 255));
	exitButton->SetBackgroundColour(wxColor(181, 136, 99));
	exitButton->SetFont(font);
	exitButton->SetForegroundColour(wxColor(255, 255, 255));
	
	wxBoxSizer* buttonSizer = new wxBoxSizer(wxVERTICAL);
	buttonSizer->AddStretchSpacer();
	buttonSizer->Add(playButton, 0, wxALL | wxALIGN_CENTER, 10);
	buttonSizer->Add(optionsButton, 0, wxALL | wxALIGN_CENTER, 10);
	buttonSizer->Add(exitButton, 0, wxALL | wxALIGN_CENTER, 10);
	buttonSizer->AddStretchSpacer();
	panel->SetSizer(buttonSizer);

	playButton->Bind(wxEVT_LEFT_DOWN, &MenuFrame::startGameButton, this);
	exitButton->Bind(wxEVT_LEFT_DOWN, &MenuFrame::exitButton, this);
	optionsButton->Bind(wxEVT_LEFT_DOWN, &MenuFrame::optionsButton, this);
	playButton->Bind(wxEVT_ENTER_WINDOW, &MenuFrame::OnHoverEnter, this);
	playButton->Bind(wxEVT_LEAVE_WINDOW, &MenuFrame::OnHoverLeave, this);
	optionsButton->Bind(wxEVT_ENTER_WINDOW, &MenuFrame::OnHoverEnter, this);
	optionsButton->Bind(wxEVT_LEAVE_WINDOW, &MenuFrame::OnHoverLeave, this);
	exitButton->Bind(wxEVT_ENTER_WINDOW, &MenuFrame::OnHoverEnter, this);
	exitButton->Bind(wxEVT_LEAVE_WINDOW, &MenuFrame::OnHoverLeave, this);

	
}

void MenuFrame::startGameButton(wxMouseEvent& evt) {
	MainFrame* mainFrame = new MainFrame("Game");
	mainFrame->SetClientSize(900, 600);
	mainFrame->SetBackgroundColour(wxColour(181, 136, 99));
	mainFrame->Center();
	mainFrame->Show();
}

void MenuFrame::optionsButton(wxMouseEvent& evt) {
	OptionsFrame* optionsFrame = new OptionsFrame("Options");
	optionsFrame->SetClientSize(500, 250);
	optionsFrame->SetBackgroundColour(wxColour(181, 136, 99));
	optionsFrame->Center();

	optionsFrame->Show();
}


void MenuFrame::exitButton(wxMouseEvent& evt) {
	wxWindow::Close();
}

void MenuFrame::OnPaint(wxPaintEvent& evt) {
	wxPaintDC dc(panel);  
	wxBitmap backgroundBitmap("menu-background.jpg", wxBITMAP_TYPE_JPEG);
	wxSize panelSize = panel->GetClientSize();

	if (backgroundBitmap.IsOk()) {
		wxImage img = backgroundBitmap.ConvertToImage();
		img.Rescale(panelSize.GetWidth(), panelSize.GetHeight(), wxIMAGE_QUALITY_HIGH);
		wxBitmap scaledBitmap(img);
		dc.DrawBitmap(scaledBitmap, 0, 0, true);
	}
}


void MenuFrame::OnHoverEnter(wxMouseEvent& event) {
	wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());
	if (button) {
		button->SetBackgroundColour(wxColor(0, 0, 0)); 
		button->Refresh(); 
	}
	event.Skip();
}

void MenuFrame::OnHoverLeave(wxMouseEvent& event) {
	wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());
	if (button) {
		button->SetBackgroundColour(wxColor(181, 136, 99)); // Original color
		button->Refresh();
	}
	event.Skip();
}
