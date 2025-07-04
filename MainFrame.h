#pragma once
#include <wx/wx.h>
#include "Board.h"
#include "Player.h"

class MainFrame :public wxFrame 
{
public:
	MainFrame(const wxString& title);
	void UpdateUI();
	bool isLegalMove();
	bool isAttack(const std::string& position);
	std::string getPieceType(int idPiece);
	void createBoard();
private:
	int selectedPiece;
	bool isPlayer1Turn;
	std::map<std::string,wxPanel*> boardPositions;
	std::map<int , std::string> piecesPositions;
	void OnPieceSelected(wxMouseEvent& evt);
	void OnPieceMoved(wxMouseEvent& evt);
	std::string movingPosition;
	std::vector<std::string> possiblePositions;
	Entities::Player* player1;
	Entities::Player* player2;
	Entities::Board* board;
	wxPanel* panel;
};
