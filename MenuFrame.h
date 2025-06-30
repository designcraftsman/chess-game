#pragma once

#include <wx/wx.h>

class MenuFrame :public wxFrame
{
public:
	MenuFrame(const wxString& title);
	void startGameButton(wxMouseEvent& evt);
	void OnPaint(wxPaintEvent& evt);
private:
	wxPanel* panel;
};

