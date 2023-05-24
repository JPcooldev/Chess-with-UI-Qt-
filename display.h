#ifndef DISPLAY_H
#define DISPLAY_H

#include "square.h"
#include "Chess/Game.hpp"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QVector>
#include <QGraphicsProxyWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QLabel>

//QT_BEGIN_NAMESPACE
//namespace Ui { class Display; }
//QT_END_NAMESPACE

const int squareSize = 80;
const int sideBoardSize = 50;

class Display : public QMainWindow
{
    Q_OBJECT

    QMainWindow mainWindow;

    // welcome page
    QWidget *welcomePage;
    QPushButton *startButton;
    QVBoxLayout *welcomePageLayout;
    QLabel *welcomeImage;
    QLabel *welcomeTitle;
    QLabel *welcomeSignature;


    // game page
    QGraphicsScene *scene;
    QGraphicsView *graphicsView;
    QVector<Square*> squaresBoard {};
    QGraphicsTextItem *titleText;
    QGraphicsTextItem *statusTextLabel;
    QGraphicsTextItem *statusText;
    QGraphicsRectItem *statusRect;
    QGraphicsTextItem *turnText;
    QGraphicsRectItem *turnRect;
    QGraphicsRectItem *rightRect;
    QGraphicsRectItem *movesRect;
    QGraphicsProxyWidget *proxyRevertMoveButton;

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

    const QString lettersBoard[8] =
    {
        "a", "b", "c", "d", "e", "f", "g", "h"
    };

    const QString numbersBoard[8] =
    {
        "1", "2", "3", "4", "5", "6", "7", "8"
    };

    Game game;
    Color turnColor {WHITE};
    QVector<QPair<QString, QString>> movesStrings;
public:
    Display(QWidget *parent = nullptr);
    ~Display();

    QGraphicsScene* getScene();
private:
    //Ui::Display *ui;
    void setupBoard(int size);
    void setupPieces();
    void setupWelcomePage();
    void setupGamePage();
    void closingEvent(QCloseEvent *event);
public slots:
    void setStatusText(const QString& str);
    void setTurnText(const QString& str);
    void getResponseFromGame(QString response);
    void logMoves(QString move);
    void colorHelp(QString location);
    void clearPossibleMovesColor(QString locFrom, QString locTo);
    void runGame();
};
#endif // DISPLAY_H
