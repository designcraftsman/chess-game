#include "OptionsFrame.h"


OptionsFrame::OptionsFrame(const wxString& title) :wxFrame(nullptr, wxID_ANY, title) {

	this->panel = new wxPanel(this);

	wxArrayString themeChoices;
	themeChoices.Add("classic");
	themeChoices.Add("premium");
	themeChoices.Add("danger");
	wxRadioBox* themeChoice = new wxRadioBox(this->panel, wxID_ANY, "Board Theme", wxDefaultPosition, wxDefaultSize,themeChoices);

	wxArrayString timeLimit;
	timeLimit.Add("None");
	timeLimit.Add("1min");
	timeLimit.Add("3min");
	timeLimit.Add("5min");
	wxRadioBox* timeChoice = new wxRadioBox(this->panel, wxID_ANY, "Time Limit", wxDefaultPosition, wxDefaultSize, timeLimit);

	SetBackgroundStyle(wxBG_STYLE_PAINT);

	wxFont font(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
	themeChoice->SetFont(font);
	timeChoice->SetFont(font);
	wxBoxSizer* buttonSizer = new wxBoxSizer(wxVERTICAL);
	buttonSizer->AddStretchSpacer();
	buttonSizer->Add(themeChoice, 0, wxALL | wxALIGN_CENTER, 10);
	buttonSizer->Add(timeChoice, 0, wxALL | wxALIGN_CENTER, 10);
	buttonSizer->AddStretchSpacer();
	this->panel->SetSizer(buttonSizer);
}

