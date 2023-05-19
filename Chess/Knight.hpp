//
//  Knight.hpp
//  Chess
//
//  Created by Jakub Prokop on 29.03.2023.
//

#ifndef Knight_hpp
#define Knight_hpp

#include "Piece.hpp"

class Knight : public Piece {
    
public:
    Knight(Color color);
    ~Knight() override = default;
    
    bool isValidMove(const Chessboard &board, const std::pair<int, int> &squareFrom, const std::pair<int, int> &squareTo) const override;
};

#endif /* Knight_hpp */
