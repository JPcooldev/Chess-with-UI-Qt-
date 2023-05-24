//
//  Chessboard.hpp
//  Chess
//
//  Created by Jakub Prokop on 28.03.2023.
//

#ifndef Chessboard_hpp
#define Chessboard_hpp

#include "typedef.h"
#include "Piece.hpp"

#include <array>
#include <vector>
#include <memory>
#include <utility>

const int boardSize = 8;

class Piece;

class Chessboard {
    //posibility to do this by std::map<std::pair<int, int>, pointer to an Piece object>
    std::array<std::array<std::unique_ptr<Piece>, boardSize>, boardSize> m_board; //{nullptr}; vyzkouset alternativa createBoard
    
    // captures hold captured Piece and its location from which it's been captured (for reverting reason)
    std::vector<std::pair<std::unique_ptr<Piece>,std::pair<int, int>>> m_captures;
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> m_moves;
    
private:
    //fills board with nullptr
    void createBoard();
    void createPieces();
    void createPawns();
    void createRooks();
    void createKnights();
    void createBishops();
    void createQueens();
    void createKings();
    //set-ups a piece at x,y location and creates an object using unique_ptr
    void placeOnBoard(const std::pair<int, int> &squareStart, std::unique_ptr<Piece> piece);
    //places a piece on given square(if capture takes place, captured piece is returned via unique_ptr, if piece moves to an empty square, it returns nullptr)
    std::unique_ptr<Piece> setPieceOnSquare(const std::pair<int, int> &squareFrom, const std::pair<int, int> &squareTo);
    
    std::string getTypeToPrint(const std::unique_ptr<Piece> &square) const;
public:
    Chessboard();
    ~Chessboard() = default;
    
    bool isForwardMove(const std::pair<int, int> &squareFrom, const std::pair<int, int> &squareTo) const;
    bool isHorizontalMove(const std::pair<int, int> &squareFrom, const std::pair<int, int> &squareTo) const;
    bool isVerticalMove(const std::pair<int, int> &squareFrom, const std::pair<int, int> &squareTo) const;
    bool isDiagonalMove(const std::pair<int, int> &squareFrom, const std::pair<int, int> &squareTo) const;
    bool isKnightMove(const std::pair<int, int> &squareFrom, const std::pair<int, int> &squareTo) const;
    bool isOnBoard(const std::pair<int, int> &square) const;
    bool isSameColor(const std::pair<int, int> &squareFrom, const std::pair<int, int> &squareTo) const;
    bool isDifferentColor(const std::pair<int, int> &squareFrom, const std::pair<int, int> &squareTo) const;
    bool isOccupied(const std::pair<int, int> &square) const;
    bool isPathFree(const std::pair<int, int> &squareFrom, const std::pair<int, int> &squareTo) const;
    bool isValidMove(const std::pair<int, int> &squareFrom, const std::pair<int, int> &squareTo) const;
    
    int getMoveLength(const std::pair<int, int> &squareFrom, const std::pair<int, int> &squareTo) const;
    std::vector<std::pair<int,int>> getPiecesLocations(Color color) const;
    std::pair<int,int> getKingsLocation(Color color) const;
    const std::unique_ptr<Piece>& getPiece(const std::pair<int, int> &square) const;
    std::vector<std::pair<int, int>> getPossibleMoves(const std::pair<int, int> &square);
    
    void revertLastMove();
    bool movePiece(const std::pair<int, int> &squareFrom, const std::pair<int, int> &squareTo);
    bool castle(const std::pair<int, int> &squareFrom, const std::pair<int, int> &squareTo) const;
    
    void printBoard() const;
    void printCaptures() const;
    void printMoves() const;
    std::string colorToString(Color color) const;
    std::string typeToString(Type type) const;
    char typeToChar(Type type) const;
};

#endif /* Chessboard_hpp */
