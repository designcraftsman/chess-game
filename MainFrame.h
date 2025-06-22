#pragma once
#include <wx/wx.h>
#include "Board.h"
#include "Player.h"

class MainFrame :public wxFrame
{
public:
	MainFrame(const wxString& title);
private:
	void OnPieceSelected(wxMouseEvent& evt);
	Entities::Player* player1;
	Entities::Player* player2;
	Entities::Board* board;
};
