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
			pieces[i].sprite.setPosition(sf::Vector2f(Holder.left + offsetx + (pieces[i].x * Holder.width / 8), Holder.top + offsety+ (pieces[i].y * Holder.height / 8)));
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
            pieces[i].sprite.setPosition(sf::Vector2f(Holder.left + offsetx + (pieces[i].x * Holder.width / 8), Holder.top + offsety +(pieces[i].y * Holder.height / 8)));
            pieces[i].sprite.setScale(Holder.width / 1600.f, Holder.height / 1600.f);
        }
    }
    if (selected != NULL) {
        selected->x = curr.X;
        selected->y = curr.Y;

        selected->sprite.setPosition(sf::Vector2f(Holder.left + offsetx +(selected->x * Holder.width / 8), Holder.top + offsety +(selected->y * Holder.height / 8)));
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
                pieces[index].isWhite = pieces[index].pieceID < 6 ? true : false;
            }
            ++index;
        }
    }
    
    font.loadFromFile("arial.ttf");

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
            if (event.mouseButton.button == sf::Mouse::Button::Left && ((whiteplayplayer && playBoard.getTurn()) || (blackplayplayer && !playBoard.getTurn())))
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
                        isSelected = 1;
                    }
                }
                else
                {
                    if (selected[0] == projX && selected[1] == projY)
                    {
                        isSelected = 0;
                    }
                    else
                    {
                        bool checkmate = false;
                        bool isMeCheckmate = false;

                        move m(selected[0], selected[1], projX, projY);
                        move bestmove = playBoard.bestMove(playBoard.currBoard, playBoard.getTurn(), 2,&checkmate, &isMeCheckmate);
                        if (bestmove.X != -1 && bestmove.oX != -1 && bestmove.Y != -1 && bestmove.oY != -1) {
                            if (playBoard.playMove(m))
                            {
                                MapPieces(m);
#pragma region Castle
                                if (playBoard.currBoard.arr[m.X][m.Y] == 4 && m.X - m.oX == 2)  
                                {
                                        MapPieces(move(7, 7, 5, 7));
                                }
                                if (playBoard.currBoard.arr[m.X][m.Y] == 4 && m.oX - m.X == 2)  
                                {
                                        MapPieces(move(0, 7, 3, 7));
                                }
                                if (playBoard.currBoard.arr[m.X][m.Y] == 10 && m.X - m.oX == 2)  
                                {
                                        MapPieces(move(0, 0, 5, 0));
                                }
                                if (playBoard.currBoard.arr[m.X][m.Y] == 10 && m.oX - m.X == 2)  
                                {
                                        MapPieces(move(0, 7, 3, 0));
                                }
#pragma endregion
                                playBoard.nextTurn();
                            }
                        }
                        if (checkmate)
                        {
                            gameover = true;
                        }
                        isSelected = 0;
                    }
                }
            }
            if (event.mouseButton.button == sf::Mouse::Button::Left && ((!whiteplayplayer && playBoard.getTurn()) || (!blackplayplayer && !playBoard.getTurn()))) {
                //std::cout << "What What\n";
                std::vector<move> AImoves = playBoard.getLegalMoves(playBoard.currBoard, playBoard.getTurn());

                bool checkmate = false;
                bool isMeCheckmate = false;
                int numMoves = AImoves.size();
                move m = playBoard.bestMove(playBoard.currBoard, playBoard.getTurn(), 4, &checkmate, &isMeCheckmate);
                if (playBoard.playMove(m))
                {
                    MapPieces(m);
#pragma region Castle
                    if (playBoard.currBoard.arr[m.X][m.Y] == 4 && m.X - m.oX == 2)
                    {
                        MapPieces(move(7, 7, 5, 7));
                    }
                    if (playBoard.currBoard.arr[m.X][m.Y] == 4 && m.oX - m.X == 2)
                    {
                        MapPieces(move(0, 7, 3, 7));
                    }
                    if (playBoard.currBoard.arr[m.X][m.Y] == 10 && m.X - m.oX == 2)
                    {
                        MapPieces(move(0, 0, 5, 0));
                    }
                    if (playBoard.currBoard.arr[m.X][m.Y] == 10 && m.oX - m.X == 2)
                    {
                        MapPieces(move(0, 0, 3, 0));
                    }
#pragma endregion
                    playBoard.nextTurn();
                }
                if (checkmate) {
                    gameover = true;
                }
            }
            else if (event.mouseButton.button == sf::Mouse::Button::Right)
            {
                isSelected = 0;
            }
            

            //std::cout << playBoard.currBoard.score; 

            break;
        case sf::Event::Closed:
            window.close();
            return false;
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape) {
                window.close();
                return false;
                break;
            }
        }

    }
    

    window.clear();
    DrawSquares();
    DrawPieces();
    if (gameover) {
        std::string a = (playBoard.getTurn() == 0 ? "white" : "black");
        text.setString(a + " wins!!");
        text2.setString("Press 'Esc' to close");
        text.setFont(font);
        text2.setFont(font);
        text.setCharacterSize(0.1*X);
        text2.setCharacterSize(0.04*X);

        text.setPosition(0.24*X, 0.425*Y);
        text2.setPosition(0.3*X, 0.625*Y);
        text.setFillColor(sf::Color::Red);
        text2.setFillColor(sf::Color::Blue);
        window.draw(text);
        window.draw(text2);
    }
    window.display();
    return true;
}
