//
//  Pawn.cpp
//  Chess
//
//  Created by Jakub Prokop on 29.03.2023.
//

#include "Pawn.hpp"

Pawn::Pawn(Color color) : Piece(PAWN, color)
{}

bool Pawn::isValidMove(const Chessboard &board, const std::pair<int, int> &squareFrom, const std::pair<int, int> &squareTo) const
{
    //capturing (must be diagonal move)
    if (board.isDiagonalMove(squareFrom, squareTo))
    {
        // on squareTo must be piece of different color and moveLength=1
        if (board.getMoveLength(squareFrom, squareTo) == 1 && board.isDifferentColor(squareFrom, squareTo))
            return true;
        else
            return false;
    }
    
    //going forward
    if (board.isForwardMove(squareFrom, squareTo))
    {
        //squareTo must be empty
        if (board.isOccupied(squareTo))
            return false;
        else
        {
            int len = board.getMoveLength(squareFrom, squareTo);
            //moveLength must be 1 or 2 but it must be first move in a game for the piece
            if (len == 1 || (len == 2 && getMoves() == 0 && board.isPathFree(squareFrom, squareTo)))
                return true;
            else
                return false;
        }
    }
    
    //EN PASSANT
    
    return false;
}
