#include "App.h"
#include "MainFrame.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);


bool App::OnInit() {
	wxImage::AddHandler(new wxPNGHandler());
	wxImage::AddHandler(new wxJPEGHandler());
	wxImage::AddHandler(new wxBMPHandler());
	MainFrame* mainFrame = new MainFrame("Chess Game");
	mainFrame->SetClientSize(900, 600);
	mainFrame->SetBackgroundColour(wxColour(200, 200, 200));
	mainFrame->Center();
	mainFrame->Show();
	return true;
}