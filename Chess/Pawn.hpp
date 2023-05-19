//
//  Pawn.hpp
//  Chess
//
//  Created by Jakub Prokop on 29.03.2023.
//

#ifndef Pawn_hpp
#define Pawn_hpp

#include "Piece.hpp"

class Pawn : public Piece {
    
public:
    Pawn(Color color);
    ~Pawn() override = default;
    
    bool isValidMove(const Chessboard &board, const std::pair<int, int> &squareFrom, const std::pair<int, int> &squareTo) const override;
};

#endif /* Pawn_hpp */
