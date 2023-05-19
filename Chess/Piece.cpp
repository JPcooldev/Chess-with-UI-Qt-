//
//  Piece.cpp
//  Chess
//
//  Created by Jakub Prokop on 28.03.2023.
//

#include "Chess/Piece.hpp"

Piece::Piece(Type type, Color color) : m_type(type), m_color(color), m_moves(0)
{}

Color Piece::getColor() const { 
    return m_color;
}

Type Piece::getType() const {
    return m_type;
}

unsigned int Piece::getMoves() const
{
    return m_moves;
}

void Piece::setMoves(int change)
{
    if (m_moves == 0 && change < 0)
        m_moves = 0;
    else
        m_moves += change;
}
