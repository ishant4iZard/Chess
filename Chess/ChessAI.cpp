#include "ChessAI.h"
#include "ChessBoard.h"
#include <thread>

move ChessAI::bestMove(board newboard, bool newturn, int depth, bool* Checkmate, bool* isMeCheckmate) {
    std::vector<move> Movesthisturn = playboard->getLegalMoves(newboard, newturn);
    int itr = 0;
    if (depth == 0) {
        move m(-1, -1, -1, -1);
        while (itr < Movesthisturn.size())
        {
            if (playboard->playMoveAI(Movesthisturn[itr], newboard, newturn, Movesthisturn)) {
                m = Movesthisturn[itr];
                break;
            }
            itr++;
        }
        return m;
    }

    std::vector<move> BestMoves;
    std::vector<move> ForcedMoves;
    move BestMove;
    int oldScore = newturn == 1 ? (-999) : (999);


    for (int i = 0; i < Movesthisturn.size(); ++i)
    {
        if (playboard->playMoveAI(Movesthisturn[i], newboard, newturn, Movesthisturn)) {
            board recursionBoard = playboard->createnewboard(Movesthisturn[i], newboard);
            bool checkmate = false;
            bool ismecheckmate = false;
            move bestOpponentMove = bestMove(recursionBoard, !newturn, depth - 1, &checkmate, &ismecheckmate);
            if (checkmate) {
                *isMeCheckmate = true;
                return Movesthisturn[i];
            }
            if (ismecheckmate) {
                ForcedMoves.push_back(Movesthisturn[i]);
                continue;
            }
            board bestOpponentBoard = playboard->createnewboard(bestOpponentMove, recursionBoard);
            int newScore = bestOpponentBoard.score;
            if ((newturn == 1 && (newScore > oldScore)) || (newturn == 0 && (oldScore > newScore))) {
                BestMoves.clear();
                BestMove = Movesthisturn[i];
                BestMoves.push_back(BestMove);
                oldScore = newScore;
            }
            if (oldScore == newScore) {
                BestMove = Movesthisturn[i];
                BestMoves.push_back(BestMove);
            }
        }
        else {
            Movesthisturn.erase(Movesthisturn.begin() + i);
            i--;
        }
    }
    if (Movesthisturn.size() == 0) {
        *Checkmate = true;
    }
    if (BestMoves.size() != 0) {
        int random = (rand() * rand() % BestMoves.size());
        BestMove = BestMoves[random];
    }
    else {
        if (ForcedMoves.size() != 0) {
            int random = (rand() * rand() % ForcedMoves.size());
            BestMove = ForcedMoves[random];
        }
    }
    return BestMove;
}

move ChessAI::MinMax(board newboard, bool newturn, bool* Checkmate) {
    int TurnMultipler = newturn ? 1 : -1;
    int opponentMinMaxScore = 999;
    move bestMove(-1, -1, -1, -1);
    std::vector<move> Movesthisturn = playboard->getLegalMoves(newboard, newturn);
    std::vector<move> BestMoves;
    std::vector<move> ForcedMoves;

    for (auto mymoves : Movesthisturn) {
        int opponentMaxScore = INT_MIN;
        int score;
        if (playboard->playMoveAI(mymoves, newboard, newturn, Movesthisturn)) {
            board recursionBoard = playboard->createnewboard(mymoves, newboard);
            std::vector<move> OpponentMovesthisTurn = playboard->getLegalMoves(recursionBoard, !newturn);
            std::vector<move> BestOpponentMoves;
            std::vector<move> ForcedOpponentMoves;

            for (auto opponentmove : OpponentMovesthisTurn) {
                if (playboard->playMoveAI(opponentmove, recursionBoard, !newturn, OpponentMovesthisTurn)) {
                    board OpponentrecursionBoard = playboard->createnewboard(opponentmove, recursionBoard);
                    score = -TurnMultipler * OpponentrecursionBoard.score;
                    if (score > opponentMaxScore) {
                        opponentMaxScore = score;
                        BestOpponentMoves.clear();
                        BestOpponentMoves.push_back(opponentmove);
                    }
                    else if (score == opponentMaxScore) {
                        BestOpponentMoves.push_back(opponentmove);
                    }
                }
            }
            if (BestOpponentMoves.size() == 0) {
                return mymoves;
            }
            if (opponentMaxScore < opponentMinMaxScore) {
                opponentMinMaxScore = opponentMaxScore;
                BestMoves.clear();
                BestMoves.push_back(mymoves);
            }
            else if (opponentMaxScore == opponentMinMaxScore) {
                BestMoves.push_back(mymoves);
            }
        }
    }
    if (BestMoves.size() == 0) {
        *Checkmate = true;
    }
    else {
        int random = (rand() * rand() % BestMoves.size());
        bestMove = BestMoves[random];
    }
    return bestMove;
}




float ChessAI::MinMaxRecursion(board newboard, bool newturn, int depth, bool* Checkmate, move& RecursionBestMove)
{
    if (depth == 0) {
        return newboard.score;
    }
    std::vector<move> Movesthisturn = playboard->getLegalMoves(newboard, newturn);
    std::vector<move> BestMoves;
    std::vector<move> ForcedMoves;

    float score;

    if (newturn) {
        float maxscore = -999;
        for (auto mymoves : Movesthisturn) {
            if (playboard->playMoveAI(mymoves, newboard, newturn, Movesthisturn)) {
                board myBoard = playboard->createnewboard(mymoves, newboard);
                bool checkmate;
                score = MinMaxRecursion(myBoard, false, depth - 1, &checkmate, RecursionBestMove);
                if (score > maxscore) {
                    maxscore = score;
                    BestMoves.clear();
                    BestMoves.push_back(mymoves);
                }
                else if (score == maxscore && depth == Depth) {
                    BestMoves.push_back(mymoves);
                }
            }
        }
        if (depth == Depth) {
            if (BestMoves.size() == 0) {
                *Checkmate = true;
            }
            if (BestMoves.size()) {
                int random = (rand() * rand() % BestMoves.size());
                RecursionBestMove = BestMoves[random];
            }
        }
        return maxscore;
    }
    else {
        float minscore = 999;
        for (auto mymoves : Movesthisturn) {
            if (playboard->playMoveAI(mymoves, newboard, newturn, Movesthisturn)) {
                board myBoard = playboard->createnewboard(mymoves, newboard);
                bool checkmate;
                score = MinMaxRecursion(myBoard, true, depth - 1, &checkmate, RecursionBestMove);
                if (score < minscore) {
                    minscore = score;
                    BestMoves.clear();
                    BestMoves.push_back(mymoves);
                }
                else if (score == minscore && depth == Depth) {
                    BestMoves.push_back(mymoves);
                }
            }
        }
        if (depth == Depth) {
            if (BestMoves.size() == 0) {
                *Checkmate = true;
            }
            if (BestMoves.size()) {
                int random = (rand() * rand() % BestMoves.size());
                RecursionBestMove = BestMoves[random];
            }
        }
        return minscore;
    }
}

move ChessAI::MinMaxRecursionhelper(board newboard, bool newturn, bool* Checkmate)
{
    move RecursionBestMove(-1, -1, -1, -1);
    MinMaxRecursion(newboard, newturn, Depth, Checkmate, RecursionBestMove);
    return RecursionBestMove;
}

float ChessAI::NegaMaxRecursion(board newboard, bool newturn, int depth, bool* Checkmate, move& RecursionBestMove)
{
    int turnMultiplier = newturn ? 1 : -1;
    if (depth == 0) {
        return turnMultiplier * newboard.score;
    }
    std::vector<move> Movesthisturn = playboard->getLegalMoves(newboard, newturn);
    std::vector<move> BestMoves;
    std::vector<move> ForcedMoves;

    float score;

    float maxscore = -999;
    for (auto mymoves : Movesthisturn) {
        if (playboard->playMoveAI(mymoves, newboard, newturn, Movesthisturn)) {

            board myBoard = playboard->createnewboard(mymoves, newboard);
            bool checkmate;
            score = -NegaMaxRecursion(myBoard, !newturn, depth - 1, &checkmate, RecursionBestMove);
            if (score > maxscore) {
                maxscore = score;
                BestMoves.clear();
                BestMoves.push_back(mymoves);
            }
            else if (score == maxscore && depth == Depth) {
                BestMoves.push_back(mymoves);
            }
        }
    }
    if (depth == Depth) {
        if (BestMoves.size() == 0) {
            *Checkmate = true;
        }
        else {
            int random = (rand() * rand() % BestMoves.size());
            RecursionBestMove = BestMoves[random];
        }
    }
    return maxscore;
}



void ChessAI::sortMoves(std::vector<move>& movesThisTurn, board newboard, bool newTurn) {
    playboard->quicksort(movesThisTurn, 0, movesThisTurn.size() - 1, newboard, newTurn);
}

float ChessAI::NegaMaxRecursionAlphaBeta(board newboard, bool newturn, int depth, bool* Checkmate, bool* Stalemate, float alpha, float beta, move& RecursionBestMove) {
    int turnMultiplier = newturn ? 1 : -1;
    if (depth >= Depth) {
        return turnMultiplier * newboard.score;
    }
    std::vector<move> Movesthisturn = playboard->getLegalMoves(newboard, newturn);

    std::vector<move> BestMoves;

    float score = -999;
    int invalidMovesCounter = 0;

    /*if (Movesthisturn.size() < 30) {
        Depth = 10;
    }
    else {
        Depth = 7;
    }*/

    float maxscore = -999;

    sortMoves(Movesthisturn, newboard, newturn);

    for (auto mymoves : Movesthisturn) {
        if (playboard->playMoveAI(mymoves, newboard, newturn, Movesthisturn)) {
            board myBoard = playboard->createnewboard(mymoves, newboard);
            bool checkmate = false;
            bool stalemate = false;
            score = -NegaMaxRecursionAlphaBeta(myBoard, !newturn, depth + 1, &checkmate, &stalemate, -beta, -alpha, RecursionBestMove);
            if (stalemate == true) {
                score = -999;
            }
            if (score > maxscore) {
                maxscore = score;
                BestMoves.clear();
                BestMoves.push_back(mymoves);
            }
            else if (score == maxscore && depth == 0 /*&& score!=-999*/) {
                BestMoves.push_back(mymoves);
            }
            if (maxscore > alpha) {
                alpha = maxscore;
            }
            if (alpha >= beta) {
                break;
            }
        }
        else {
            invalidMovesCounter++;
        }
    }
    if (invalidMovesCounter == Movesthisturn.size() && !playboard->isInCheck(newboard, newturn)) {
        *Stalemate = true;
        return 0;
    }
    if (depth == 0) {
        if (BestMoves.size() == 0) {
            *Checkmate = true;
        }
        else {
            int random = (rand() % BestMoves.size());
            RecursionBestMove = BestMoves[random];
        }
    }
    return maxscore;
}


float ChessAI::NegaMaxRecursionAlphaBetaThreads(board newboard, bool newturn, int depth, bool* Checkmate, bool* Stalemate, float alpha, float beta, move& RecursionBestMove) {
    int turnMultiplier = newturn ? 1 : -1;
    if (depth >= Depth) {
        return turnMultiplier * newboard.score;
    }

    std::vector<move> Movesthisturn = playboard->getLegalMoves(newboard, newturn);
    float maxscore = -999;
    std::vector<move> BestMoves;

    int invalidMovesCounter = 0;

    // Adjust depth dynamically
    /*if (Movesthisturn.size() < 30) {
        Depth = 10;
    }
    else {
        Depth = 7;
    }*/

    sortMoves(Movesthisturn, newboard, newturn);

    std::vector<std::thread> threads;
    std::vector<float> scores(Movesthisturn.size());


    for (size_t i = 0; i < Movesthisturn.size(); ++i) {
        threads.emplace_back([&, i]() {
            float score = -999;
            move mymoves = Movesthisturn[i];
            if (playboard->playMoveAI(mymoves, newboard, newturn, Movesthisturn)) {
                board myBoard = playboard->createnewboard(mymoves, newboard);
                bool checkmate = false;
                bool stalemate = false;
                score = -NegaMaxRecursionAlphaBeta(myBoard, !newturn, depth + 1, &checkmate, &stalemate, -beta, -alpha, RecursionBestMove);

                if (stalemate == true) {
                    score = -999;
                }
            }
            else {
                score = -999; // Invalid move, give it a low score
                invalidMovesCounter++;
            }
            scores[i] = score;
            });
    }

    for (auto& t : threads) {
        t.join();
    }

    if (invalidMovesCounter == Movesthisturn.size() && depth == 1 && !playboard->isInCheck(newboard, newturn)) {
        *Stalemate = true;
        return 0;
    }
    if (invalidMovesCounter == Movesthisturn.size() && depth == 0 && playboard->isInCheck(newboard, newturn)) {
        *Checkmate = true;
        return 0;
    }

    for (size_t i = 0; i < Movesthisturn.size(); ++i) {
        float score = scores[i];
        if (score > maxscore) {
            maxscore = score;
            BestMoves.clear();
            BestMoves.push_back(Movesthisturn[i]);
        }
        else if (score == maxscore && depth == 0) {
            BestMoves.push_back(Movesthisturn[i]);
        }
        if (maxscore > alpha) {
            if (maxscore > 999) {
                if (depth == Depth)
                    RecursionBestMove = Movesthisturn[i];

                return maxscore;
            }
            alpha = maxscore;
        }
        /*if (alpha >= beta) {
            break;
        }*/
    }

    if (depth == 0) {
        int random = (rand() % BestMoves.size());
        RecursionBestMove = BestMoves[random];
    }

    return maxscore;
}

move ChessAI::NegaMaxRecursionhelper(board newboard, bool newturn, bool* Checkmate, bool* Stalemate, int depth)
{
    Depth = depth;
    move RecursionBestMove(-1, -1, -1, -1);
    float alpha = -999;
    float beta = 999;
    //bool staleMate = false;
    NegaMaxRecursionAlphaBetaThreads(newboard, newturn, 0, Checkmate, Stalemate, alpha, beta, RecursionBestMove);
    //NegaMaxRecursion(newboard, newturn, Depth, Checkmate,RecursionBestMove);
    //MinMax(newboard, newturn, Checkmate);
    //MinMaxRecursion(newboard, newturn, Depth, Checkmate, RecursionBestMove);


    return RecursionBestMove;
}