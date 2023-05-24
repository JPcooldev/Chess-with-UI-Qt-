//
//  Game.hpp
//  Chess
//
//  Created by Jakub Prokop on 29.03.2023.
//

#ifndef Game_hpp
#define Game_hpp

#include "Chessboard.hpp"

#include <QString>
#include <QObject>
#include <QVector>
#include <QPair>


class Game : public QObject
{
    Q_OBJECT

    Chessboard m_chessboard;
    
public:
    Game() = default;
    ~Game() = default;
    
    void run();
    QVector<QString> searchPossibleMoves(QString square);
    void setPossibleMoves(QVector<QString> moves);
    const QVector<QString>& getPossibleMoves() const;
    void clearPossibleMoves();
private:
    void castle();
    
    void print();
    bool isInCheck(Color color) const;
    bool isInCheckMate(Color color);
    bool isInStalemate(Color color);
    Color whoTurn(int moveCount);
    bool isRightTurn(const std::pair<int, int> &coord, Color turn);
    
    std::string whoTurnDisplay(Color color);
    
    void splitStringBySpace(const std::string &input, std::vector<std::string> &tmp);
    std::pair<int, int> textToCoordinates(const std::string &textCoord);

private:
    std::string m_move1 {""};
    std::string m_move2 {""};
    Color m_turn {WHITE};
    int m_moveCounter {0};
    QVector<QString> m_possibleMoves {};
    bool helpActivated {false};

    void resetMoves();
    void setTurn(Color turn);
    void changeMoveCounter(int change);
    QString whoTurnDisplayQString(Color color);

    const QString squareNames[64] =
    {
        "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
        "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
        "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
        "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
        "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
        "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
        "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
        "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1"
    };
public slots:
    void getInput(QString input);
signals:
    void sendResponseToDisplay(QString response);
    void sendLocationOfSquareToClearColor(QString location);
    void sendLocationToGetHelp(QString location);
    void signalClearPossibleMovesColor(QString locFrom, QString locTo);
    void signalChangeColorOfSquare(QString squarename);
};

#endif /* Game_hpp */
