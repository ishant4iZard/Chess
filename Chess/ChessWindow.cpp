#include "ChessWindow.h"
#include<iostream>

void ChessWindow::SetPiecePositionAndScale(ChessPiece& piece) {
    piece.sprite.setPosition(sf::Vector2f(
        Holder.left + offsetx + (piece.x * Holder.width / 8),
        Holder.top + offsety + (piece.y * Holder.height / 8)
    ));
    piece.sprite.setScale(Holder.width / 1600.f, Holder.height / 1600.f);
}

void ChessWindow::UpdatePiecePosition(ChessPiece* piece, int newX, int newY) {
    if (piece != NULL) {
        piece->x = newX;
        piece->y = newY;
        SetPiecePositionAndScale(*piece);
    }
}

void ChessWindow::FitToHolder() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Squares[i][j].setPosition(sf::Vector2f(Holder.left + (i * Holder.width / 8), Holder.top + (j * Holder.height / 8)));
			Squares[i][j].setSize(sf::Vector2f(Holder.width / 8, Holder.height / 8));
			Squares[i][j].setFillColor((i + j) % 2 == 1 ? color[0] : color[1]);
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
            SetPiecePositionAndScale(pieces[i]);
		}
	}
}

void ChessWindow::MapPieces(move curr)
{
    ChessPiece* selected = NULL;
    for (int i = 0; i < 64; ++i)
    {
        if (pieces[i].draw == 1)
        {
            if (pieces[i].x == curr.oldPos.X && pieces[i].y == curr.oldPos.Y)
            {
                selected = &pieces[i];
            }
            if (pieces[i].x == curr.newPos.X && pieces[i].y == curr.newPos.Y)
            {
                pieces[i].draw = 0;
            }
            SetPiecePositionAndScale(pieces[i]);
        }
    }
    UpdatePiecePosition(selected, curr.newPos.X, curr.newPos.Y);
}

void ChessWindow::MapPromotion(move curr)
{
    ChessPiece* selected = NULL;
    for (int i = 0; i < 64; ++i)
    {
        if (pieces[i].draw == 1)
        {
            if (pieces[i].x == curr.oldPos.X && pieces[i].y == curr.oldPos.Y)
            {
                selected = &pieces[i];
            }
            if (pieces[i].x == curr.newPos.X && pieces[i].y == curr.newPos.Y)
            {
                pieces[i].draw = 0;
            }
            SetPiecePositionAndScale(pieces[i]);
        }
    }
    if (selected != NULL) {
        UpdatePiecePosition(selected, curr.newPos.X, curr.newPos.Y);

        selected->pieceID = playBoard.currBoard.arr[curr.newPos.X][curr.newPos.Y];
        selected->sprite.setTexture(pieceTex[selected->pieceID]);

        SetPiecePositionAndScale(*selected);
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
    AI = new ChessAI(playBoard);
}

bool ChessWindow::GameUpdate() {
    window.clear();
    DrawSquares();
    DrawPieces();

    if (gameover || Stalemate) {
        std::string message = Stalemate ? "Draw by Stalemate!!" : (playBoard.getTurn() == 0 ? "White Wins!" : "Black Wins!");
        text.setString(message);

        text2.setString("Press 'Esc' to close");
        text.setFont(font);
        text2.setFont(font);
        text.setCharacterSize(0.1 * X);
        text2.setCharacterSize(0.04 * X);

        text.setPosition(0.24 * X, 0.425 * Y);
        text2.setPosition(0.3 * X, 0.625 * Y);
        text.setFillColor(sf::Color::Red);
        text2.setFillColor(sf::Color::Blue);
        window.draw(text);
        window.draw(text2);
    }

    window.display();

    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Resized:
            HandleResizeEvent();
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
                        bool stalemate = false;

                        move m(selected[0], selected[1], projX, projY);
                        //move bestmove = playBoard.bestMove(playBoard.currBoard, playBoard.getTurn(), 2,&checkmate, &stalemate);
                        move bestmove = AI->NegaMaxRecursionhelper(playBoard.currBoard, playBoard.getTurn(), &checkmate, &stalemate, 2);

                        tryAndMakeMove(m, checkmate, stalemate);
                       
                        isSelected = 0;
                    }
                }
            }

            else if (event.mouseButton.button == sf::Mouse::Button::Right)
            {
                isSelected = 0;
            }

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


    

    if (((!whiteplayplayer && playBoard.getTurn()) || (!blackplayplayer && !playBoard.getTurn()))) {

        bool checkmate = false;
        bool stalemate = false;
        move m = AI->NegaMaxRecursionhelper(playBoard.currBoard, playBoard.getTurn(), &checkmate, &stalemate);
        //move m = playBoard.bestMove(playBoard.currBoard, playBoard.getTurn(), 4, &checkmate, &isMeCheckmate);
        //move m = playBoard.MinMaxRecursionhelper(playBoard.currBoard, playBoard.getTurn(), &checkmate);
        tryAndMakeMove(m, checkmate, stalemate);
    }

    return true;
}

bool ChessWindow::StartUpdate() {
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
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape) {
                window.close();
                return false;
                break;
            }
            if (event.key.code == sf::Keyboard::Num1) {
                if (gamestate == GameState::initial) {
                    whiteplayplayer = 1;
                    blackplayplayer = 1;
                    gamestate = GameState::startGame;
                }
                if (gamestate == GameState::humanVsAi) {
                    whiteplayplayer = 1;
                    blackplayplayer = 0;
                    gamestate = GameState::startGame;
                }
            }
            if (event.key.code == sf::Keyboard::Num2) {
                if (gamestate == GameState::initial) {
                    gamestate = GameState::humanVsAi;
                }
            }
            if (event.key.code == sf::Keyboard::Num3) {
                if (gamestate == GameState::initial) {
                    whiteplayplayer = 0;
                    blackplayplayer = 0;
                    gamestate = GameState::startGame;
                }
                if (gamestate == GameState::humanVsAi) {
                    whiteplayplayer = 0;
                    blackplayplayer = 1;
                    gamestate = GameState::startGame;
                }
            }

            break;
        }
    }
    window.clear();
    DrawSquares();
    DrawPieces();
    switch (gamestate)
    {
    case none:
        break;
    case initial:
        text.setString("Press NUM1 to Start Human Vs Human");
        text2.setString("Press NUM2 to Start Human Vs AI");
        text3.setString("Press NUM3 to Start AI Vs AI");
        text.setFont(font);
        text2.setFont(font);
        text3.setFont(font);
        text.setCharacterSize (0.05 * X);
        text2.setCharacterSize(0.05 * X);
        text3.setCharacterSize(0.05 * X);

        text.setPosition (0.06 * X, 0.3 * Y);
        text2.setPosition(0.12 * X, 0.45 * Y);
        text3.setPosition(0.18 * X, 0.6 * Y);
        text.setFillColor (sf::Color::Red);
        text2.setFillColor(sf::Color::Red);
        text3.setFillColor(sf::Color::Red);
        window.draw(text);
        window.draw(text2);
        window.draw(text3);
        break;
    case humanVsAi:
        text.setString ("Press NUM1 to Start Human as White");
        text2.setString("Press NUM3 to Start Human as Black");
        //text3.setString("Press NUM3 to Start AI Vs AI");
        text.setFont(font);
        text2.setFont(font);
        //text3.setFont(font);
        text.setCharacterSize(0.05 * X);
        text2.setCharacterSize(0.05 * X);
        //text3.setCharacterSize(0.05 * X);

        text.setPosition(0.07 * X, 0.4 * Y);
        text2.setPosition(0.07 * X, 0.55 * Y);
        //text3.setPosition(0.18 * X, 0.6 * Y);
        text.setFillColor(sf::Color::Red);
        text2.setFillColor(sf::Color::Red);
        text3.setFillColor(sf::Color::Red);
        window.draw(text);
        window.draw(text2);
        //window.draw(text3);
        break;
    case startGame:
        break;
    default:
        break;
    }
    window.display();

    return true;
}

bool ChessWindow::Update()
{
    if (gamestate != GameState::startGame) {
        return StartUpdate();
    }
    else{
        return GameUpdate();
    }
}

void ChessWindow::HandleResizeEvent() {
    X = window.getSize().x;
    Y = window.getSize().y;
    window.setView(sf::View(sf::FloatRect(0, 0, X, Y)));
    if (X > Y) {
        Holder.width = Y;
        Holder.height = Y;
        Holder.left = X / 2 - Holder.width / 2;
        Holder.top = 0;
    } else {
        Holder.width = X;
        Holder.height = X;
        Holder.top = Y / 2 - Holder.height / 2;
        Holder.left = 0;
    }
    MapPieces();
    FitToHolder();
}

void ChessWindow::tryAndMakeMove(move m, bool checkmate, bool stalemate) {
    if (checkmate) {
        gameover = true;
        return;
    }
    if (stalemate) {
        Stalemate = true;
        gameover = true;
        return;
    }
    if (playBoard.playMove(m))
    {
        handleCastleRights(m);

        if ((pieces[m.oldPos.X * 8 + m.oldPos.Y].pieceID == 6 && m.newPos.Y == 0) || 
            (pieces[m.oldPos.X * 8 + m.oldPos.Y].pieceID == 0 && m.newPos.Y == 7)) {
            MapPromotion(m);
        }
        else {
            MapPieces(m);
            handleCastleMoves(m);
        }
        playBoard.nextTurn();
    }
}

void ChessWindow::handleCastleRights(move m)
{
    if (playBoard.currBoard.arr[m.newPos.X][m.newPos.Y] == 4) {
        playBoard.canwKingKcastle = false;
        playBoard.canwKingQcastle = false;
    }
    if (playBoard.currBoard.arr[m.newPos.X][m.newPos.Y] == 10) {
        playBoard.canbKingKcastle = false;
        playBoard.canbKingQcastle = false;
    }
    if ((m.oldPos.X == 7 && m.oldPos.Y == 7) || (m.newPos.X == 7 && m.newPos.Y == 7)) {
        playBoard.canwKingKcastle = false;
    }
    if ((m.oldPos.X == 0 && m.oldPos.Y == 7) || (m.newPos.X == 0 && m.newPos.Y == 7)) {
        playBoard.canwKingQcastle = false;
    }
    if ((m.oldPos.X == 7 && m.oldPos.Y == 0) || (m.newPos.X == 7 && m.newPos.Y == 0)) {
        playBoard.canbKingKcastle = false;
    }
    if ((m.oldPos.X == 0 && m.oldPos.Y == 0) || (m.newPos.X == 0 && m.newPos.Y == 0)) {
        playBoard.canbKingQcastle = false;
    }
}

void ChessWindow::handleCastleMoves(move m)
{
    if (playBoard.currBoard.arr[m.newPos.X][m.newPos.Y] == 4 && m.newPos.X - m.oldPos.X == 2)
    {
        MapPieces(move(7, 7, 5, 7));
    }
    if (playBoard.currBoard.arr[m.newPos.X][m.newPos.Y] == 4 && m.oldPos.X - m.newPos.X == 2)
    {
        MapPieces(move(0, 7, 3, 7));
    }
    if (playBoard.currBoard.arr[m.newPos.X][m.newPos.Y] == 10 && m.newPos.X - m.oldPos.X == 2)
    {
        MapPieces(move(7, 0, 5, 0));
    }
    if (playBoard.currBoard.arr[m.newPos.X][m.newPos.Y] == 10 && m.oldPos.X - m.newPos.X == 2)
    {
        MapPieces(move(0, 7, 3, 0));
    }
}

bool ChessWindow::Update()
{
    if (gamestate != GameState::startGame) {
        return StartUpdate();
    }
    else{
        return GameUpdate();
    }
}
