#include "App.h"
#include "MenuFrame.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);


bool App::OnInit() {
	wxImage::AddHandler(new wxPNGHandler());
	wxImage::AddHandler(new wxJPEGHandler());
	wxImage::AddHandler(new wxBMPHandler());
	MenuFrame* menuFrame = new MenuFrame("DesignCraftsMan Menu");
	menuFrame->SetBackgroundColour(wxColour(77, 77, 77));
	menuFrame->Center();
	menuFrame->Show();
	menuFrame->ShowFullScreen(true);
	return true;
}