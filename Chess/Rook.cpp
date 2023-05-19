//
//  Rook.cpp
//  Chess
//
//  Created by Jakub Prokop on 29.03.2023.
//

#include "Rook.hpp"

Rook::Rook(Color color) : Piece(ROOK, color)
{}

bool Rook::isValidMove(const Chessboard &board, const std::pair<int, int> &squareFrom, const std::pair<int, int> &squareTo) const
{
    //rook can only move in horizontal or vertical directiion
    if (board.isHorizontalMove(squareFrom, squareTo) || board.isVerticalMove(squareFrom, squareTo))
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
