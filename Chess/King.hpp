#include "Piece.hpp"//
//  King.hpp
//  Chess
//
//  Created by Jakub Prokop on 29.03.2023.
//

#ifndef King_hpp
#define King_hpp


class King : public Piece {
    
public:
    King(Color color);
    ~King() override = default;
    
    bool isValidMove(const Chessboard &board, const std::pair<int, int> &squareFrom, const std::pair<int, int> &squareTo) const override;
};
#endif /* King_hpp */
