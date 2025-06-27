#pragma once
#include <wx/wx.h>
#include "Board.h"
#include "Player.h"

class MainFrame :public wxFrame
{
public:
	MainFrame(const wxString& title);
	void UpdateUI();
	boolean isLegalMove();
	boolean isAttack(int idPiece);
private:
	int selectedPiece;
	boolean isPlayer1Turn;
	std::map<int, std::string> boardPositions;
	void OnPieceSelected(wxMouseEvent& evt);
	void OnPieceMoved(wxMouseEvent& evt);
	std::string movingPosition;
	std::vector<std::string> possiblePositions;
	Entities::Player* player1;
	Entities::Player* player2;
	Entities::Board* board;
	wxPanel* panel;
};
