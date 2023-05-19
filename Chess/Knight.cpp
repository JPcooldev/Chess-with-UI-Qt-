//
//  Knight.cpp
//  Chess
//
//  Created by Jakub Prokop on 29.03.2023.
//

#include "Knight.hpp"

Knight::Knight(Color color) : Piece(KNIGHT, color)
{}

bool Knight::isValidMove(const Chessboard &board, const std::pair<int, int> &squareFrom, const std::pair<int, int> &squareTo) const
{
    //knight is able to move only in knight-like move
    if (board.isKnightMove(squareFrom, squareTo))
    {
        //fails if squareTo is occupied by piece from player's team
        if (board.isSameColor(squareFrom, squareTo))
            return false;
        
        return true;
    }
    else
        return false;
}
