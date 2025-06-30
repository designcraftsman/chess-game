#include "App.h"
#include "MenuFrame.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);


bool App::OnInit() {
	wxImage::AddHandler(new wxPNGHandler());
	wxImage::AddHandler(new wxJPEGHandler());
	wxImage::AddHandler(new wxBMPHandler());
	MenuFrame* menuFrame = new MenuFrame("DesignCraftsMan Menu");
	menuFrame->SetClientSize(900, 600);
	menuFrame->SetBackgroundColour(wxColour(200, 200, 200));
	menuFrame->Center();
	menuFrame->Show();
	return true;
}