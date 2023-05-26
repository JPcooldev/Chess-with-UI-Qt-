//
//  Game.cpp
//  Chess
//
//  Created by Jakub Prokop on 29.03.2023.
//

#include "Game.hpp"
#include "Piece.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>
#include <QDebug>
#include <QString>

void Game::run()
{
    int moveCounter = 1;
    Color turn = whoTurn(moveCounter);
    
    std::cout << "Welcome to CHESS GAME\n\n";
    
    while (true)
    {
        

        // determines if player is in checkmate
        if (isInCheckMate(turn))
        {
            std::cout << whoTurnDisplay(turn) << " is in checkmate. Game over.\n";
            break;
        }
        
        //determines if player is in stalemate
        if (isInStalemate(turn)) {
            std::cout << whoTurnDisplay(turn) << " is in stalemate. It is a draw.\n";
            break;
        }
        
        
        print();
        
        // INPUT SECTION
        // user puts input (e.g "a4 a5" or "a4 command")
        std::cout << whoTurnDisplay(turn) << "'s turn\n";
        std::cout << "Enter move: ";
        std::string input {};
        std::getline(std::cin, input);
        
        // checks for non-move commands
        if (input == "exit")
        {
            std::cout << "Game over\n";
            break;
        }
        else if (input == "revert")
        {
            m_chessboard.revertLastMove();
            moveCounter++;
            turn = whoTurn(moveCounter);
            continue;
        }
        else if (input == "captures")
        {
            m_chessboard.printCaptures();
            continue;
        }
        
        std::vector<std::string> coordinatesStr {};
        splitStringBySpace(input, coordinatesStr);
        
        std::pair<int, int> coordsFrom {textToCoordinates(coordinatesStr.at(0))};
        std::pair<int, int> coordsTo {textToCoordinates(coordinatesStr.at(1))};
        
        // CHECK INPUT
        // check if player chose occupied square (square with piece) and if so, if he chose his piece
        if ( ! isRightTurn(coordsFrom, turn) )
        {
            std::cout << "Invalid move\n";
            continue;
        }
        
        // checks is move is valid, oherwise player will move again
        if ( m_chessboard.movePiece(coordsFrom, coordsTo) )
        {
            if ( isInCheck(turn))
            {
                std::cout << "Invalid move: This leaves " << whoTurnDisplay(turn) << " in check\n";
                m_chessboard.revertLastMove();
                continue;
            }
            else
            {
                moveCounter++;
                turn = whoTurn(moveCounter);
            }
        }
        else
        {
            std::cout << "Invalid move\n";
            continue;
        }
    }
}

// determones if player get himself into check by his move
bool Game::isInCheck(Color defendingColor) const
{
    Color attackingColor {};
    if (defendingColor == WHITE)
        attackingColor = BLACK;
    else
        attackingColor = WHITE;
    
    std::pair<int, int> kingLoc = m_chessboard.getKingsLocation(defendingColor);
    std::vector<std::pair<int, int>> attackLocations = m_chessboard.getPiecesLocations(attackingColor);
    
    // check if attacking's piece can attack player's king
    for (auto &attackPiece : attackLocations)
    {
        if (m_chessboard.isValidMove(attackPiece, kingLoc))
            return true;
    }
    return false;
}

// is in check and has no legal moves
bool Game::isInCheckMate(Color defendingColor)
{
    if (isInCheck(defendingColor))
    {
        //auto& board = m_chessboard.getBoard();
        
        // get all defending's pieces and try all their possible moves, if one can stop king from being in check => no checkmate
        for (const auto &pieceLoc : m_chessboard.getPiecesLocations(defendingColor))
        {
            // trying all moves for defending's pieces
            for (int row = 0; row < boardSize; row++)
            {
                for (int square = 0; square < boardSize; square++)
                {
                    std::pair<int, int> locationToMove = std::make_pair(row, square);
                    if ( m_chessboard.movePiece(pieceLoc, locationToMove) )
                    {
                        // player is no longer in check, so there exists possible move
                        if ( ! isInCheck(defendingColor))
                        {
                            m_chessboard.revertLastMove();
                            return false;
                        }
                        // move did not help with defending check so it must be reverted
                        m_chessboard.revertLastMove();
                    }
                }
            }
        }
        // no move is possible to defend checkmate => end
        return true;
    }
    else
        return false;
}

// is not in check and there are no legal moves
bool Game::isInStalemate(Color defendingColor)
{
    if ( isInCheck(defendingColor) )
        return false;
    else
    {
        //auto& board = m_chessboard.getBoard();
        
        // get all defending's pieces and try all their possible moves, if one can stop king from being in check => no checkmate
        for (const auto &pieceLoc : m_chessboard.getPiecesLocations(defendingColor))
        {
            // trying all moves for defending's pieces
            for (int row = 0; row < boardSize; row++)
            {
                for (int square = 0; square < boardSize; square++)
                {
                    std::pair<int, int> locationToMove = std::make_pair(row, square);
                    if ( m_chessboard.movePiece(pieceLoc, locationToMove) )
                    {
                        // player find a move which does not put him in check => no stalemate
                        if ( ! isInCheck(defendingColor))
                        {
                            m_chessboard.revertLastMove();
                            return false;
                        }
                        // move put player into check, it must be reverted
                        m_chessboard.revertLastMove();
                    }
                }
            }
        }
    }
    // all possible moves put player into check => stalemate
    return true;
}

//returns who's turn it is
Color Game::whoTurn(int moveCount)
{
    if (moveCount % 2 == 1)
        return WHITE;
    else
        return BLACK;
}

//converts user input (e.g. "a2 a3", "a2 possibilities" or "exit" ...) to separate strings
void Game::splitStringBySpace(const std::string& input, std::vector<std::string>& tmp)
{
    std::istringstream iss(input);
    std::string buf {};
    
    while (iss >> buf)
        tmp.emplace_back(buf);
}
 
//converts text coordinates into board indexes
std::pair<int, int> Game::textToCoordinates(const std::string &textCoord)
{
    int y = textCoord[0] - 'a';
    int x = '8' - textCoord[1];
    return {x, y};
}

void Game::print()
{
    m_chessboard.printBoard();
}

//checks if player wants to move with his piece
bool Game::isRightTurn(const std::pair<int, int> &coord, Color turn)
{
    if (m_chessboard.isOccupied(coord))
        return m_chessboard.getPiece(coord)->getColor() == turn;
    else
        return false;
}

std::string Game::whoTurnDisplay(Color color)
{
    return (color == WHITE ? "WHITE" : "BLACK");
}

void Game::getInput(QString input)
{
    //qDebug() << "Game saw that " << input << "was clicked, and will now respond.";

    if (m_move1 == "")
    {
        m_move1 = input.toStdString();
        emit sendResponseToDisplay("Choosing piece");

        std::pair<int, int> squareFrom {textToCoordinates(m_move1)};

        if (m_chessboard.getPiece(squareFrom) == nullptr)
        {
            qDebug() << "first click: empty square selected";

            emit sendResponseToDisplay("Empty square selected");
            emit sendLocationOfSquareToClearColor(QString::fromStdString(m_move1));
            resetMoves();
        }
        else
        {
            if (isRightTurn(squareFrom, m_turn))
            {
                qDebug() << "first click: " << input << " (valid)";

                helpActivated = true;
                emit sendLocationToGetHelp(input);
            }
            else
            {
                qDebug() << "first click: not right turn";

                emit sendResponseToDisplay("Not right turn");
                emit sendLocationOfSquareToClearColor(QString::fromStdString(m_move1));
                resetMoves();
            }
        }
    }
    else
    {
        qDebug() << "second click: " << input;

        m_move2 = input.toStdString();

        emit sendLocationOfSquareToClearColor(QString::fromStdString(m_move1));
        emit sendLocationOfSquareToClearColor(QString::fromStdString(m_move2));

        if (helpActivated)
        {
            helpActivated = false;
            emit signalClearPossibleMovesColor(QString::fromStdString(m_move1), QString::fromStdString(m_move2));
        }

        std::pair<int, int> squareFrom {textToCoordinates(m_move1)};
        std::pair<int, int> squareTo {textToCoordinates(m_move2)};

        QString move1_QString {QString::fromStdString(m_move1)};
        QString move2_QString {QString::fromStdString(m_move2)};

        if (m_chessboard.movePiece(squareFrom, squareTo))
        {

            qDebug() << "Move is eligible";

            if ( isInCheck(m_turn))
            {
                qDebug() << "Invalid move: This leaves " << whoTurnDisplayQString(m_turn) << " in check";
                m_chessboard.revertLastMove();
                emit sendResponseToDisplay("Invalid move");
                resetMoves();
                return;
            }
            else
            {
                qDebug() << "Game allows this move and will let Display proceed";

                if (m_turn == WHITE)
                    setTurn(BLACK);
                else
                    setTurn(WHITE);

                QString response {move1_QString + move2_QString};
                emit sendResponseToDisplay(response);

                if (response ==  "e1c1")
                    emit sendResponseToDisplay("White queenside castle");
                else if (response ==  "e1g1")
                    emit sendResponseToDisplay("White kingside castle");
                else if (response == "e8c8")
                    emit sendResponseToDisplay("Black queenside castle");
                else if (response ==  "e8g8")
                    emit sendResponseToDisplay("Black kingside castle");

                resetMoves();
            }

            if ( isInCheckMate(m_turn))
                emit sendResponseToDisplay("Checkmate");
            else if ( isInStalemate(m_turn))
                emit sendResponseToDisplay("Stalemate");
            else if ( isInCheck(m_turn))
                emit sendResponseToDisplay("Check");
        }
        else
        {
            qDebug() << "Move is not eligible";

            /* move is not valid, but user might click on his other piece
             * meaning, he wants to activate help for this piece
             */
            if (m_chessboard.getPiece(squareTo) == nullptr)
            {
                qDebug() << "second click: empty square selected";

                emit sendResponseToDisplay("Empty square selected");
                resetMoves();
                return;
            }
            else
            {
                if (m_chessboard.getPiece(squareTo)->getColor() == m_turn)
                {
                    qDebug() << "second click on same color -> get help";

                    resetMoves();
                    emit signalChangeColorOfSquare(input);
                    getInput(input);
                    return;
                }
                else
                {
                    qDebug() << "second click: not right turn";

                    emit sendResponseToDisplay("Invalid move");
                    resetMoves();
                    return;
                }
            }
        }
    }
}

void Game::resetMoves()
{
    m_move1 = "";
    m_move2 = "";
}

void Game::setTurn(Color turn)
{
    m_turn = turn;
}

void Game::changeMoveCounter(int change)
{
    if (m_moveCounter == 0  &&  change < 0)
        return;
    else
        m_moveCounter += change;
}

QString Game::whoTurnDisplayQString(Color color)
{
    return (color == WHITE ? "WHITE" : "BLACK");
}

QVector<QString> Game::searchPossibleMoves(QString square)
{
    QVector<QString> possibleMoves {};

    std::pair<int, int> squareCoords {textToCoordinates(square.toStdString())};
    std::vector<std::pair<int, int>> moves {m_chessboard.getPossibleMoves(squareCoords)};

    for (const auto &location : moves)
    {
        QString locName = squareNames[location.second + location.first*8];
        possibleMoves.push_back(locName);
    }

    return possibleMoves;
}

const QVector<QString>& Game::getPossibleMoves() const
{
    return m_possibleMoves;
}

void Game::clearPossibleMoves()
{
    m_possibleMoves.clear();
}
