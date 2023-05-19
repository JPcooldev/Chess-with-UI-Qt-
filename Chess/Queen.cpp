//
//  Queen.cpp
//  Chess
//
//  Created by Jakub Prokop on 29.03.2023.
//

#include "Queen.hpp"

Queen::Queen(Color color) : Piece(QUEEN, color)
{}

bool Queen::isValidMove(const Chessboard &board, const std::pair<int, int> &squareFrom, const std::pair<int, int> &squareTo) const
{
    // move must be horizontal, vertical or diagonal
    if (board.isHorizontalMove(squareFrom, squareTo) || board.isVerticalMove(squareFrom, squareTo) || board.isDiagonalMove(squareFrom, squareTo))
    {
        // path must be free
        if (board.isPathFree(squareFrom, squareTo))
        {
            // destinaton must be empty or opponent's piece
            if (board.isOccupied(squareTo) && board.isSameColor(squareFrom, squareTo))
                return false;
            
            return true;
        }
    }
    
    return false;
}
