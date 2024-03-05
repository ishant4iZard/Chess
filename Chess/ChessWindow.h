#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "ChessPiece.h"
#include "ChessBoard.h"

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
	ChessPiece pieces[64];
	ChessBoard playBoard;
	int selected[2];
	bool isSelected = 0;
	int X, Y;

	void FitToHolder();
	void DrawSquares();
	void MapPieces();
	void DrawPieces();
	void MapPieces(move curr);

	int offsetx = 5, offsety = 0;


	bool gameover;
	//bool startgame = false;
	
public:

	bool whiteplayplayer =0, blackplayplayer = 1;
	ChessWindow(int width, int height, const char* name, const char* imgPath[12]);
	bool Update();
	//~ChessWindow();
};
