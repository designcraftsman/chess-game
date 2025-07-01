#pragma once

#include <wx/wx.h>

class MenuFrame :public wxFrame
{
public:
	MenuFrame(const wxString& title);
	void startGameButton(wxMouseEvent& evt);
	void OnPaint(wxPaintEvent& evt);
	void exitButton(wxMouseEvent& evt);
	void optionsButton(wxMouseEvent& evt);
	void OnHoverEnter(wxMouseEvent& event);
	void OnHoverLeave(wxMouseEvent& event);
private:
	wxPanel* panel;
};

