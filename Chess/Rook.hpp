//
//  Rook.hpp
//  Chess
//
//  Created by Jakub Prokop on 29.03.2023.
//

#ifndef Rook_hpp
#define Rook_hpp

#include "Piece.hpp"

class Rook : public Piece {
    
public:
    Rook(Color color);
    ~Rook() override = default;
    
    bool isValidMove(const Chessboard &board, const std::pair<int, int> &squareFrom, const std::pair<int, int> &squareTo) const override;
};

#endif /* Rook_hpp */
