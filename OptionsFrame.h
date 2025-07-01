#pragma once

#include <wx/wx.h>

class OptionsFrame : public wxFrame
{
public:
	OptionsFrame(const wxString& title);
private:
	wxPanel* panel;
};

