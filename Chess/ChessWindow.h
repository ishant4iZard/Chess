#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "ChessPiece.h"
#include "ChessBoard.h"
#include "ChessAI.h"

enum GameState {
	none,
	initial,
	humanVsAi,
	startGame
};

class ChessWindow
{
private:
	sf::RenderWindow window;
	sf::RectangleShape Squares[8][8];
	sf::IntRect Holder;
	sf::Color color[2];
	sf::Texture pieceTex[12];
	sf::Font font;
	sf::Text text;
	sf::Text text2;
	sf::Text text3;
	ChessPiece pieces[64];
	ChessBoard playBoard;
	ChessAI* AI;
	int selected[2];
	bool isSelected = 0;
	int X, Y;

	void SetPiecePositionAndScale(ChessPiece& piece);
	void UpdatePiecePosition(ChessPiece* piece, int newX, int newY);

	void FitToHolder();
	void DrawSquares();
	void MapPieces();
	void DrawPieces();
	void MapPieces(move curr);
	void MapPromotion(move curr);

	void HandleResizeEvent();
	void tryAndMakeMove(move m, bool checkmate, bool stalemate);
	void handleCastleRights(move m);
	void handleCastleMoves(move m);

	int offsetx = 5, offsety = 0;

	bool gameover, Stalemate;
	
public:

	bool whiteplayplayer =1, blackplayplayer = 0;
	ChessWindow(int width, int height, const char* name, const char* imgPath[12]);
	bool Update();


	bool GameUpdate();
	bool StartUpdate();

	GameState gamestate = GameState::initial;
	~ChessWindow() {
		delete AI;
	}
};
