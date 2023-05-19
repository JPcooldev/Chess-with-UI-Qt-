//
//  Queen.hpp
//  Chess
//
//  Created by Jakub Prokop on 29.03.2023.
//

#ifndef Queen_hpp
#define Queen_hpp

#include "Piece.hpp"

class Queen : public Piece {
    
public:
    Queen(Color color);
    ~Queen() override = default;
    
    bool isValidMove(const Chessboard &board, const std::pair<int, int> &squareFrom, const std::pair<int, int> &squareTo) const override;
};

#endif /* Queen_hpp */
