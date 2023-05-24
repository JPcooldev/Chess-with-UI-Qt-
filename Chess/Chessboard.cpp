//
//  Chessboard.cpp
//  Chess
//
//  Created by Jakub Prokop on 28.03.2023.
//
//   0  1  2  3  4  5  6  7
//0  BR BN BB BQ BK BB BN BR  P - PAWN
//1  BP BP BP BP BP BP BP BP  R - ROOK
//2  -- -- -- -- -- -- -- --  N - KNIGHT
//3  -- -- -- -- -- -- -- --  B - BISHOP
//4  -- -- -- -- -- -- -- --  Q - QUEEN
//5  -- -- -- -- -- -- -- --  K - KING
//6  WP WP WP WP WP WP WP WP
//7  WR WN WB WQ WK WB WN WR
//

#include "Chessboard.hpp"
#include "Piece.hpp"
#include "Pawn.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Queen.hpp"
#include "King.hpp"

#include <utility>
#include <iostream>
#include <memory>

Chessboard::Chessboard()
{
    createBoard();
    createPieces();
}

void Chessboard::createPieces() {
    createPawns();
    createRooks();
    createKnights();
    createBishops();
    createQueens();
    createKings();
}

void Chessboard::createPawns() {
    placeOnBoard(std::make_pair(6, 0), std::make_unique<Pawn>(WHITE));
    placeOnBoard(std::make_pair(6, 1), std::make_unique<Pawn>(WHITE));
    placeOnBoard(std::make_pair(6, 2), std::make_unique<Pawn>(WHITE));
    placeOnBoard(std::make_pair(6, 3), std::make_unique<Pawn>(WHITE));
    placeOnBoard(std::make_pair(6, 4), std::make_unique<Pawn>(WHITE));
    placeOnBoard(std::make_pair(6, 5), std::make_unique<Pawn>(WHITE));
    placeOnBoard(std::make_pair(6, 6), std::make_unique<Pawn>(WHITE));
    placeOnBoard(std::make_pair(6, 7), std::make_unique<Pawn>(WHITE));
    
    placeOnBoard(std::make_pair(1, 0), std::make_unique<Pawn>(BLACK));
    placeOnBoard(std::make_pair(1, 1), std::make_unique<Pawn>(BLACK));
    placeOnBoard(std::make_pair(1, 2), std::make_unique<Pawn>(BLACK));
    placeOnBoard(std::make_pair(1, 3), std::make_unique<Pawn>(BLACK));
    placeOnBoard(std::make_pair(1, 4), std::make_unique<Pawn>(BLACK));
    placeOnBoard(std::make_pair(1, 5), std::make_unique<Pawn>(BLACK));
    placeOnBoard(std::make_pair(1, 6), std::make_unique<Pawn>(BLACK));
    placeOnBoard(std::make_pair(1, 7), std::make_unique<Pawn>(BLACK));
}

void Chessboard::createRooks() {
    placeOnBoard(std::make_pair(7, 0), std::make_unique<Rook>(WHITE));
    placeOnBoard(std::make_pair(7, 7), std::make_unique<Rook>(WHITE));
    
    placeOnBoard(std::make_pair(0, 0), std::make_unique<Rook>(BLACK));
    placeOnBoard(std::make_pair(0, 7), std::make_unique<Rook>(BLACK));
}

void Chessboard::createKnights() {
    placeOnBoard(std::make_pair(7, 1), std::make_unique<Knight>(WHITE));
    placeOnBoard(std::make_pair(7, 6), std::make_unique<Knight>(WHITE));
    
    placeOnBoard(std::make_pair(0, 1), std::make_unique<Knight>(BLACK));
    placeOnBoard(std::make_pair(0, 6), std::make_unique<Knight>(BLACK));
}

void Chessboard::createBishops() {
    placeOnBoard(std::make_pair(7, 2), std::make_unique<Bishop>(WHITE));
    placeOnBoard(std::make_pair(7, 5), std::make_unique<Bishop>(WHITE));
    
    placeOnBoard(std::make_pair(0, 2), std::make_unique<Bishop>(BLACK));
    placeOnBoard(std::make_pair(0, 5), std::make_unique<Bishop>(BLACK));
}

void Chessboard::createQueens() {
    placeOnBoard(std::make_pair(7, 3), std::make_unique<Queen>(WHITE));
    
    placeOnBoard(std::make_pair(0, 3), std::make_unique<Queen>(BLACK));
}

void Chessboard::createKings() {
    placeOnBoard(std::make_pair(7, 4), std::make_unique<King>(WHITE));
    
    placeOnBoard(std::make_pair(0, 4), std::make_unique<King>(BLACK));
}

// fills board with nullptr
void Chessboard::createBoard()
{
    for (auto& row : m_board)
        for (auto& a : row)
            a.reset(nullptr);
}

// moves ownership of a piece to the board (more precisily to the square(x,y) of a board
void Chessboard::placeOnBoard(const std::pair<int, int>& squareStart, std::unique_ptr<Piece> piece)
{
    m_board[squareStart.first][squareStart.second] = std::move(piece);
}

// checks if WHITE piece is moving upwards and if BLACK is moving downwards
bool Chessboard::isForwardMove(const std::pair<int, int> &squareFrom, const std::pair<int, int> &squareTo) const
{
    Color color = m_board[squareFrom.first][squareFrom.second]->getColor();
    if (color == WHITE && squareFrom.first > squareTo.first)
        return true;
    else if (color == BLACK && squareFrom.first < squareTo.first)
        return true;
    else
        return false;
}

//checks if row is unchanged, then it is horizontal move
bool Chessboard::isHorizontalMove(const std::pair<int, int> &squareFrom, const std::pair<int, int> &squareTo) const
{
    return squareFrom.first == squareTo.first;
}

//checks if column is unchanged, then it is vertical move
bool Chessboard::isVerticalMove(const std::pair<int, int> &squareFrom, const std::pair<int, int> &squareTo) const
{
    return squareFrom.second == squareTo.second;
}

// checks if the differences between moves in horizontal and vertical direction are the same, then it is diagonal move
bool Chessboard::isDiagonalMove(const std::pair<int, int> &squareFrom, const std::pair<int, int> &squareTo) const
{
    int verticalDifference = abs(squareFrom.second - squareTo.second);
    int horizontalDifference = abs(squareFrom.first - squareTo.first);
    return verticalDifference == horizontalDifference;
}

//checks if the differences between moves in horizontal and vertical direction are in the L-shape, then it is knight move
bool Chessboard::isKnightMove(const std::pair<int, int> &squareFrom, const std::pair<int, int> &squareTo) const
{
    int verticalDifference = abs(squareFrom.second - squareTo.second);
    int horizontalDifference = abs(squareFrom.first - squareTo.first);
    return ((verticalDifference == 2 && horizontalDifference == 1) || (verticalDifference == 1 && horizontalDifference == 2));
}

//checks if row and column is in (0,7) interval
bool Chessboard::isOnBoard(const std::pair<int, int> &square) const
{
    int xloc = square.first;
    int yloc = square.second;
    return (xloc >= 0 && xloc < boardSize && yloc >= 0 && yloc < boardSize);
}

//checks if square is occupied then if colors match, otherwise square isn't the same color
bool Chessboard::isSameColor(const std::pair<int, int> &squareFrom, const std::pair<int, int> &squareTo) const
{
    if (isOccupied(squareTo))
        return (m_board[squareFrom.first][squareFrom.second]->getColor() == m_board[squareTo.first][squareTo.second]->getColor());
    else
        return false;
}

//checks if square is occupied then if colors are different, otherwise square is the same color
bool Chessboard::isDifferentColor(const std::pair<int, int> &squareFrom, const std::pair<int, int> &squareTo) const
{
    //return ! (isSameColor(squareFrom, squareTo));
    if (isOccupied(squareTo))
        return (m_board[squareFrom.first][squareFrom.second]->getColor() != m_board[squareTo.first][squareTo.second]->getColor());
    else
        return false;
}

//checks if a square has some value or nullptr (which means it is empty)
bool Chessboard::isOccupied(const std::pair<int, int> &square) const
{
    if (m_board[square.first][square.second] == nullptr)
        return false;
    else
        return true;
}

//checks if path is clear, some pieces cannot jump over
bool Chessboard::isPathFree(const std::pair<int, int> &squareFrom, const std::pair<int, int> &squareTo) const
{
    //for horizontal move
    if (isHorizontalMove(squareFrom, squareTo))
    {
        //evaluating due to dirrection in for loop
        if (squareFrom.second >= squareTo.second)
        {
            for (int i = squareFrom.second - 1; i > squareTo.second; i--)
                if (isOccupied(std::make_pair(squareFrom.first, i)))
                    return false;
            return true;
        }
        else
        {
            for (int i = squareFrom.second + 1; i < squareTo.second; i++)
                if (isOccupied(std::make_pair(squareFrom.first, i)))
                    return false;
            return true;
        }
    }
    //for vertical move
    else if (isVerticalMove(squareFrom, squareTo))
    {
        if (squareFrom.first >= squareTo.first)
        {
            for (int i = squareFrom.first - 1; i > squareTo.first; i--)
                if (isOccupied(std::make_pair(i, squareFrom.second)))
                    return false;
            return true;
        }
        else
        {
            for (int i = squareFrom.first + 1; i < squareTo.first; i++)
                if (isOccupied(std::make_pair(i, squareFrom.second)))
                    return false;
            return true;
        }
    }
    //for diagonal move
    else if (isDiagonalMove(squareFrom, squareTo))
    {
        bool movingUp = squareFrom.first >= squareTo.first ? true : false;
        bool movingLeft = squareFrom.second >= squareTo.second ? true : false;
        
        int length = getMoveLength(squareFrom, squareTo);
        
        if (length == 1)
        {
            return true;
        }
        else
        {
            int i = 1;
            int j = 1;
            
            for (int len = 1; len < length; len++)
            {
                if (movingUp)
                    i = -1 * len;
                else
                    i = len;
                
                if (movingLeft)
                    j = -1 * len;
                else
                    j = len;
                
                if (isOccupied(std::make_pair(squareFrom.first + i, squareFrom.second + j)))
                    return false;
                
            }
            return true;
        }
    }
    
    return false;
}

//returns move length
int Chessboard::getMoveLength(const std::pair<int, int> &squareFrom, const std::pair<int, int> &squareTo) const
{
    if (isVerticalMove(squareFrom, squareTo) || isDiagonalMove(squareFrom, squareTo))
        return abs(squareFrom.first - squareTo.first);
    else if (isHorizontalMove(squareFrom, squareTo))
        return abs(squareFrom.second - squareTo.second);
    else
        return -1;
    
}

//returns a piece from board (for reading)
const std::unique_ptr<Piece>& Chessboard::getPiece(const std::pair<int, int> &square) const
{
    return m_board[square.first][square.second];
}

//
bool Chessboard::movePiece(const std::pair<int, int> &squareFrom, const std::pair<int, int> &squareTo)
{
    // checks if move is on board
    if ( ! isOnBoard(squareFrom) || ! isOnBoard(squareTo))
        return false;
    
    // move to the same location is invalid move
    if (squareFrom == squareTo)
        return false;
    
    // check if move is valid
    if ( ! isValidMove(squareFrom, squareTo))
        return false;

    // castle
    if (getPiece(squareFrom)->getType() == KING && getMoveLength(squareFrom, squareTo) == 2)
    {
        // move king
        std::unique_ptr<Piece> remainderFromMoveKing = setPieceOnSquare(squareFrom, squareTo);

        std::pair<int, int> rookFrom;
        std::pair<int, int> rookTo;

        // castle to left
        if (squareFrom.second > squareTo.second)
        {
            rookFrom = std::make_pair(squareFrom.first, 0);
            rookTo = std::make_pair(squareFrom.first, squareFrom.second - 1);
        }
        else
        {
            rookFrom = std::make_pair(squareFrom.first, 7);
            rookTo = std::make_pair(squareFrom.first, squareFrom.second + 1);
        }

        // move rook
        std::unique_ptr<Piece> remainderFromMoveRook = setPieceOnSquare(rookFrom, rookTo);

        m_board[squareTo.first][squareTo.second]->setMoves(+1);

        m_moves.emplace_back(std::make_pair(rookFrom, rookTo));
        m_moves.emplace_back(std::make_pair(squareFrom, squareTo));

        return true;
    }

    // makes move and possibly captured piece puts into captures
    std::unique_ptr<Piece> remainderFromMove = setPieceOnSquare(squareFrom, squareTo);
    
    m_board[squareTo.first][squareTo.second]->setMoves(+1);
    
    // save move
    m_moves.emplace_back(std::make_pair(squareFrom, squareTo));
    
    if (remainderFromMove != nullptr)
        m_captures.emplace_back(std::make_pair(std::move(remainderFromMove), squareTo));
    
    return true;
}

bool Chessboard::castle(const std::pair<int, int> &squareFrom, const std::pair<int, int> &squareTo) const
{
    std::pair<int, int> rookLeft {std::make_pair(squareFrom.first, 0)};
    std::pair<int, int> rookRight {std::make_pair(squareFrom.first, 7)};

    // castle left
    if (squareFrom.second > squareTo.second)
    {
        return (getPiece(rookLeft)->getType() == ROOK && getPiece(rookLeft)->getMoves() == 0 && isPathFree(squareFrom, rookLeft));
    }
    else if (squareFrom.second < squareTo.second)
    {
        return (getPiece(rookRight)->getType() == ROOK && getPiece(rookRight)->getMoves() == 0 && isPathFree(squareFrom, rookRight));
    }
    else
        return false;
}

std::unique_ptr<Piece> Chessboard::setPieceOnSquare(const std::pair<int, int> &squareFrom, const std::pair<int, int> &squareTo)
{
    //piece (to captures) or nullptr from squareTo, which we will return
    std::unique_ptr<Piece> old = std::move(m_board[squareTo.first][squareTo.second]);
    
    //move piece
    m_board[squareTo.first][squareTo.second] = std::move(m_board[squareFrom.first][squareFrom.second]);
    
    //set squareFrom as empty
    m_board[squareFrom.first][squareFrom.second].reset(nullptr);
    
    return old;
}

//prints board
void Chessboard::printBoard() const
{
    int i = 8;
    std::cout << std::endl;
    for (const auto &row : m_board)
    {
        std::cout << i << "  ";
        for (const auto &square : row)
            std::cout << getTypeToPrint(square) << " ";
        std::cout << std::endl;
        i--;
    }
    std::cout << "   a  b  c  d  e  f  g  h\n" << std::endl;
}

//prints specific string depending on what's on square
std::string Chessboard::getTypeToPrint(const std::unique_ptr<Piece> &square) const
{
    if (square == nullptr)
        return "--";
    else
    {
        Color color = square->getColor();
        
        switch (square->getType())
        {
            case PAWN:
                return (color == WHITE ? "WP" : "BP");
            case ROOK:
                return (color == WHITE ? "WR" : "BR");
            case KNIGHT:
                return (color == WHITE ? "WN" : "BN");
            case BISHOP:
                return (color == WHITE ? "WB" : "BB");
            case QUEEN:
                return (color == WHITE ? "WQ" : "BQ");
            case KING:
                return (color == WHITE ? "WK" : "BK");
            default:
                return "getTypeToPrint error";
        }
    }
    
}

// return possible moves for given piece
std::vector<std::pair<int, int>> Chessboard::getPossibleMoves(const std::pair<int, int> &squareFrom)
{
    std::vector<std::pair<int, int>> locations {};

    for (int row = 0; row < int(m_board.size()); row++)
    {
        for (int square = 0; square < int(m_board[row].size()); square++)
        {
            std::pair<int, int> location { std::make_pair(row, square) };
            if (isValidMove(squareFrom, location))
            {
                locations.emplace_back(location);
            }
        }
    }
    return locations;
}

// return location on color's pieces which are on board
std::vector<std::pair<int,int>> Chessboard::getPiecesLocations(Color color) const
{
    std::vector<std::pair<int, int>> locations {};
    
    for (int row = 0; row < int(m_board.size()); row++)
    {
        for (int square = 0; square < int(m_board[row].size()); square++)
        {
            std::pair<int, int> location { std::make_pair(row, square) };
            // square is empty, continue search
            if ( ! isOccupied(location) )
                continue;
            
            if (m_board[row][square]->getColor() == color)
                locations.emplace_back(location);
        }
    }
    return locations;
}

// return location of color's king
std::pair<int,int> Chessboard::getKingsLocation(Color color) const
{
    std::pair<int, int> kingLoc {};
    for (int row = 0; row < int(m_board.size()); row++)
    {
        for (int square = 0; square < int(m_board[row].size()); square++)
        {
            std::pair<int, int> location { std::make_pair(row, square) };
            // square is empty, continue search
            if ( ! isOccupied(location) )
                continue;
            
            if (m_board[row][square]->getColor() == color && m_board[row][square]->getType() == KING)
                kingLoc = location;
        }
    }
    return kingLoc;
}

// checks if move from to to is valid
bool Chessboard::isValidMove(const std::pair<int, int> &from, const std::pair<int, int> &to) const
{
    if (from == to)
        return false;

    // if piece is king which has not moved yet, check for castling
    if (getPiece(from)->getType() == KING && getPiece(from)->getMoves() == 0 &&
        getMoveLength(from, to) == 2 && isHorizontalMove(from, to))
    {
        if (castle(from, to))
            return true;
    }

    if (m_board[from.first][from.second]->isValidMove(*this, from, to))
        return true;
    else
        return false;
}

// reverts last move
void Chessboard::revertLastMove()
{
    // get coordinates of last move (in reverse order) and delete the move
    std::pair<int, int> from {m_moves.back().second};
    std::pair<int, int> to {m_moves.back().first};
    m_moves.pop_back();
    
    // reverting castling
    if (getPiece(from)->getType() == KING && getMoveLength(from, to) == 2)
    {
        std::pair<int, int> fromRook {m_moves.back().second};
        std::pair<int, int> toRook {m_moves.back().first};
        m_moves.pop_back();

        std::unique_ptr<Piece> remainderFromMoveKing = setPieceOnSquare(from, to);
        std::unique_ptr<Piece> remainderFromMoveRook = setPieceOnSquare(fromRook, toRook);

        m_board[to.first][to.second]->setMoves(-1);
        return;
    }

    // revert last move
    std::unique_ptr<Piece> remainderFromMove = setPieceOnSquare(from, to);
    
    m_board[to.first][to.second]->setMoves(-1);
    
    if ( ! m_captures.empty())
    {
        // return back captured piece (if something was captured)
        std::pair<int, int> capturedLocation {m_captures.back().second};
        
        if (capturedLocation == from)
        {
            m_board[from.first][from.second] = std::move(m_captures.back().first);
            m_captures.pop_back();
        }
    }
}

std::string Chessboard::colorToString(Color color) const
{
    if (color == WHITE)
        return "White";
    else
        return "Black";
}

std::string Chessboard::typeToString(Type type) const
{
    std::string strType;
    switch (type)
    {
        case PAWN: strType = "Pawn"; break;
        case ROOK: strType = "Rook"; break;
        case KNIGHT: strType = "Knight"; break;
        case BISHOP: strType = "Bishop"; break;
        case QUEEN: strType = "Queen"; break;
        //case KING:
        default: break;
    }
    return strType;
}

char Chessboard::typeToChar(Type type) const
{
    char t;
    switch (type)
    {
        case PAWN: t = ' '; break;
        case ROOK: t = 'R'; break;
        case KNIGHT: t = 'N'; break;
        case BISHOP: t = 'B'; break;
        case QUEEN: t = 'Q'; break;
        case KING: t = 'K'; break;
        default: break;
    }
    return t;
}

void Chessboard::printCaptures() const
{
    std::cout << std::endl;
    
    if (m_captures.empty())
        std::cout << "No captures.\n";
    else
    {
        for (const auto &capture : m_captures)
        {
            std::cout << colorToString(capture.first->getColor()) << " " << typeToString(capture.first->getType()) << std::endl;
        }
    }
}

/*
void Chessboard::printMoves() const
{
    std::cout << std::endl;
    if (m_moves.empty())
        std::cout << "No moves.\n";
    else
    {
        int i = 1;
        for (const auto &move : m_moves)
        {
            Type type = boa
            std::cout << i << ". " << typeToChar(
        }
    }
}
*/
