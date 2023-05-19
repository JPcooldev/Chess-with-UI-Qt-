//
//  King.cpp
//  Chess
//
//  Created by Jakub Prokop on 29.03.2023.
//

#include "King.hpp"

King::King(Color color) : Piece(KING, color)
{}

bool King::isValidMove(const Chessboard &board, const std::pair<int, int> &squareFrom, const std::pair<int, int> &squareTo) const
{
    //king cannot move to the square occupied by his team
    if (board.getMoveLength(squareFrom, squareTo) == 1)
    {
        // square is empty or there is a piece of different color
        if ( ! board.isOccupied(squareTo)  ||  board.isDifferentColor(squareFrom, squareTo))
            return true;
        else
            return false;
    }
    else
        return false;
}
