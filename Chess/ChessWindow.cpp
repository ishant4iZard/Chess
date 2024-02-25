#include "ChessWindow.h"
#include<iostream>

void ChessWindow::FitToHolder() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Squares[i][j].setPosition(sf::Vector2f(Holder.left + (i * Holder.width / 8), Holder.top + (j * Holder.height / 8)));
			Squares[i][j].setSize(sf::Vector2f(Holder.width / 8, Holder.height / 8));
			Squares[i][j].setFillColor((i + j) % 2 == 0 ? color[0] : color[1]);
		}
	}
}

void ChessWindow::DrawSquares() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			window.draw(Squares[i][j]);
		}
	}
}

void ChessWindow::DrawPieces()
{
	for (int i = 0; i < 64; ++i)
	{
		if (pieces[i].draw == 1)
		{
			window.draw(pieces[i].sprite);
		}
	}
}

void ChessWindow::MapPieces()
{
	for (int i = 0; i < 64; ++i)
	{
		if (pieces[i].draw == 1)
		{
			pieces[i].sprite.setPosition(sf::Vector2f(Holder.left + (pieces[i].x * Holder.width / 8), Holder.top + (pieces[i].y * Holder.height / 8)));
			pieces[i].sprite.setScale(Holder.width / 1600.f, Holder.height / 1600.f);
		}
	}
}

void ChessWindow::MapPieces(move curr)
{
    ChessPiece* selected = NULL;
    bool capture = false;
    for (int i = 0; i < 64; ++i)
    {
        if (pieces[i].draw == 1)
        {
            if (pieces[i].x == curr.oX && pieces[i].y == curr.oY)
            {
                selected = &pieces[i];
            }
            if (pieces[i].x == curr.X && pieces[i].y == curr.Y)
            {
                pieces[i].draw = 0;
                //sounds[2].play();
                capture = true;
            }
            pieces[i].sprite.setPosition(sf::Vector2f(Holder.left + (pieces[i].x * Holder.width / 8), Holder.top + (pieces[i].y * Holder.height / 8)));
            pieces[i].sprite.setScale(Holder.width / 1600.f, Holder.height / 1600.f);
        }
    }
    if (selected != NULL) {
        selected->x = curr.X;
        selected->y = curr.Y;

        //if (!capture)
        //{
        //    //sounds[0].play();
        //}
        selected->sprite.setPosition(sf::Vector2f(Holder.left + (selected->x * Holder.width / 8), Holder.top + (selected->y * Holder.height / 8)));
        selected->sprite.setScale(Holder.width / 1600.f, Holder.height / 1600.f);
    }
}



ChessWindow::ChessWindow(int width, int height, const char* name, const char* imgPath[12])
{
    color[0].r = 118;
    color[0].g = 150;
    color[0].b = 86;
    color[1].r = 238;
    color[1].g = 238;
    color[1].b = 210;
    X = width;
    Y = height;
    Holder.left = 0;
    Holder.top = 0;
    Holder.width = width;
    Holder.height = height;
    
    FitToHolder();
    sf::IntRect blank;
    for (int i = 0; i < 12; ++i)
    {
        pieceTex[i].loadFromFile(imgPath[i], blank);
    }
    int index = 0;
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            pieces[index].pieceID = playBoard.currBoard.arr[i][j];
            pieces[index].x = i;
            pieces[index].y = j;
            if (pieces[index].pieceID != -1)
            {
                pieces[index].sprite.setTexture(pieceTex[pieces[index].pieceID], true);
                pieces[index].draw = 1;
            }
            ++index;
        }
    }
    
    MapPieces();
    window.create(sf::VideoMode(width, height), name);
}

bool ChessWindow::Update()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Resized:
            X = window.getSize().x;
            Y = window.getSize().y;
            window.setView(sf::View(sf::FloatRect(0, 0, X, Y)));
            if (X > Y)
            {
                Holder.width = Y;
                Holder.height = Y;
                Holder.left = X / 2 - Holder.width / 2;
                Holder.top = 0;
            }
            else
            {
                Holder.width = X;
                Holder.height = X;
                Holder.top = Y / 2 - Holder.height / 2;
                Holder.left = 0;
            }
            MapPieces();
            FitToHolder();
            break;
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Button::Left && playBoard.getTurn())
            {
                int pX, pY;
                pX = event.mouseButton.x;
                pY = event.mouseButton.y;
                int projX, projY;
                projX = ((pX - Holder.left) - ((pX - Holder.left) % (Holder.width / 8))) / (Holder.width / 8);
                projY = ((pY - Holder.top) - ((pY - Holder.top) % (Holder.height / 8))) / (Holder.height / 8);
                if (isSelected == 0)
                {
                    if (pX >= Holder.left && pX <= Holder.left + Holder.width && pY > Holder.top && pY < Holder.top + Holder.height)
                    {
                        selected[0] = projX;
                        selected[1] = projY;
                        //Squares[selected[0]][selected[1]].setFillColor(sf::Color(186, 202, 68));
                        isSelected = 1;
                    }
                }
                else
                {
                    if (selected[0] == projX && selected[1] == projY)
                    {
                        //Squares[selected[0]][selected[1]].setFillColor(color[1 - ((selected[0] + selected[1]) % 2)]);
                        isSelected = 0;
                    }
                    else
                    {
                        move m(selected[0], selected[1], projX, projY);
                        if (playBoard.playMove(m))
                        {
                            MapPieces(m);
                            playBoard.nextTurn();
                        }
                        //Squares[selected[0]][selected[1]].setFillColor(color[1 - ((selected[0] + selected[1]) % 2)]);
                        isSelected = 0;
                    }
                }
            }
            else if (event.mouseButton.button == sf::Mouse::Button::Right)
            {
                //Squares[selected[0]][selected[1]].setFillColor(color[1 - ((selected[0] + selected[1]) % 2)]);
                isSelected = 0;
            }
            

            std::cout << playBoard.score();

            break;
        case sf::Event::Closed:
            window.close();
            return false;
            break;
        }
    }
    if (!playBoard.getTurn()) {
        std::cout << "What What\n";
        std::vector<move> AImoves = playBoard.getLegalMoves(playBoard.currBoard, playBoard.getTurn());
        int numMoves = AImoves.size();
        move m = playBoard.bestMove(playBoard.currBoard, playBoard.getTurn(), 3);
        if (playBoard.playMove(m)) {
            MapPieces(m);
            playBoard.nextTurn();
        }
    }

    window.clear();
    DrawSquares();
    DrawPieces();
    window.display();
    return true;
}
