#pragma once
#include "SFML/Graphics.hpp"

enum Piece {
	Pawn	,
	Knight	,
	Bishop	,
	Rook	,
	Queen	,
	King	,
	None
};

class ChessPiece
{
public:
	sf::Sprite sprite;
	Piece piece;
	int x, y;
	bool isWhite , draw =1;
	int pieceID;


	void moves();
	void captures();


private:

};

