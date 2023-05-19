//
//  Bishop.cpp
//  Chess
//
//  Created by Jakub Prokop on 29.03.2023.
//

#include "Bishop.hpp"

Bishop::Bishop(Color color) : Piece(BISHOP, color)
{}

bool Bishop::isValidMove(const Chessboard &board, const std::pair<int, int> &squareFrom, const std::pair<int, int> &squareTo) const
{
    //checks if it is a diagonal move
    if (board.isDiagonalMove(squareFrom, squareTo))
    {
        //fails if the path is not clear
        if ( ! board.isPathFree(squareFrom, squareTo))
            return false;
        
        //fails if squareTo is occupied by piece from player's team
        if (board.isSameColor(squareFrom, squareTo))
            return false;
        
        return true;
    }
    else
        return false;
}

