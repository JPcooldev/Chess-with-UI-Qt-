#include "display.h"
//#include "Chess/Chessboard.hpp"
//#include "ui_display.h"

#include <QObject>
#include <QPair>
#include <QMessageBox>

Display::Display(QWidget *parent)
    : QMainWindow(parent)
    //, ui(new Ui::Display)
{
    setupWelcomePage();
}

void Display::setupGamePage()
{
    QObject::connect(&game, &Game::sendResponseToDisplay, this, &Display::getResponseFromGame);

    QObject::connect(&game, &Game::sendLocationToGetHelp, this, &Display::colorHelp);
    QObject::connect(&game, &Game::signalClearPossibleMovesColor, this, &Display::clearPossibleMovesColor);

    scene = new QGraphicsScene();
    setupBoard(squareSize);
    setupPieces();

    titleText = new QGraphicsTextItem("Chess game");
    titleText->setPos(squaresBoard[3]->rect().left(), squaresBoard[0]->pos().y()- 40 - sideBoardSize);
    titleText->setScale(1.5);

    statusRect = new QGraphicsRectItem();
    statusRect->setRect(squaresBoard[7]->rect().right() + sideBoardSize + 5, squaresBoard[7]->rect().top(),
                        250, squareSize);
    statusRect->setBrush(Qt::white);

    statusText = new QGraphicsTextItem("Let's start");
    statusText->setParentItem(statusRect);
    statusText->setPos(statusRect->boundingRect().x() + 20,
                       statusRect->boundingRect().y() + statusRect->boundingRect().height()/2
                       - statusText->boundingRect().height()/2);
    statusText->setDefaultTextColor(Qt::black);
    statusText->setScale(1.3);

    turnRect = new QGraphicsRectItem();
    turnRect->setRect(squaresBoard[15]->rect().right() + sideBoardSize + 5, squaresBoard[15]->rect().top() + 5,
                      250, squareSize - 5);
    turnRect->setBrush(Qt::white);

    turnText = new QGraphicsTextItem("White's Turn");
    turnText->setParentItem(turnRect);
    turnText->setPos(turnRect->boundingRect().x() + 20,
                     turnRect->boundingRect().y() + turnRect->boundingRect().height()/2
                     - turnText->boundingRect().height()/2);
    turnText->setDefaultTextColor(Qt::black);
    turnText->setScale(1.3);

    statusTextLabel = new QGraphicsTextItem("Status:");
    statusTextLabel->setPos(squaresBoard[7]->boundingRect().right() + sideBoardSize + 10,
                            //statusRect->boundingRect().width()/2 - statusTextLabel->boundingRect().width()/2,
                            squaresBoard[7]->boundingRect().top() - statusTextLabel->boundingRect().height() - 10);
    statusTextLabel->setScale(1.3);

    movesRect = new QGraphicsRectItem();
    movesRect->setRect(squaresBoard[55]->boundingRect().right() + sideBoardSize + 5,
                       squaresBoard[55]->boundingRect().top(),
                       150, 2*squareSize);
    movesRect->setBrush(Qt::white);

    scene->addItem(titleText);
    scene->addItem(statusTextLabel);
    scene->addItem(statusRect);
    scene->addItem(turnRect);
    //scene->addItem(movesRect);

    graphicsView = new QGraphicsView(scene);
    graphicsView->setFixedSize(1000, 800);
    graphicsView->show();
}

void Display::setupWelcomePage()
{
    welcomePage = new QWidget();
    welcomePage->setFixedSize(400, 300);
    welcomePage->setStyleSheet("background-color: black;");

    welcomeTitle = new QLabel("Welcome to game of chess");
    welcomeTitle->setAlignment(Qt::AlignCenter);
    welcomeTitle->setStyleSheet("font-size: 30px;");

    welcomeSignature = new QLabel("Made by Jakub Prokop");
    welcomeSignature->setAlignment(Qt::AlignCenter);

    startButton = new QPushButton("Start", welcomePage);
    startButton->setGeometry(200 - startButton->width()/2, 200, 80, 45);
    QFont font = startButton->font();
    font.setPointSize(font.pointSize() + 15);
    startButton->setFont(font);
    startButton->setStyleSheet("background-color: gray;");

    welcomeImage = new QLabel();
    QPixmap image("/Users/jp/Desktop/dev/qt/projects/ChessGame/images/welcomePageImage.png");
    welcomeImage->setPixmap(image);
    welcomeImage->setScaledContents(true);

    welcomePageLayout = new QVBoxLayout(welcomePage);
    welcomePageLayout->addStretch();
    welcomePageLayout->addWidget(welcomeTitle);
    welcomePageLayout->addWidget(welcomeSignature);
    welcomePageLayout->addWidget(welcomeImage);
    welcomePageLayout->addWidget(startButton);
    welcomePageLayout->addStretch();

    welcomePage->setLayout(welcomePageLayout);

    setCentralWidget(welcomePage);

    QObject::connect(startButton, &QPushButton::clicked,
                     this, &Display::runGame);
}

void Display::runGame()
{
    setupGamePage();
    this->hide();
}

void Display::setupBoard(int size)
{
    QColor whiteColor(223, 191, 159);
    QColor blackColor(96, 64, 32);

    QBrush whiteBrush(whiteColor);
    QBrush blackBrush(blackColor);

    int x = 0;
    int y = 0;

    for (int row = 0; row < boardSize; row++)
    {
        for (int col = 0; col < boardSize; col++)
        {
            Square *square = new Square(x, y, size);

            square->setName(squareNames[row * boardSize + col]);
            squaresBoard.push_back(square);
            scene->addItem(square);

            if ((row + col) % 2 == 0)
                square->setBrush(whiteBrush);
            else
                square->setBrush(blackBrush);

            QObject::connect(square, &Square::clicked,
                             &game, &Game::getInput);
            QObject::connect(&game, &Game::sendLocationOfSquareToClearColor,
                             square, &Square::clearColor);
            QObject::connect(&game, &Game::signalChangeColorOfSquare,
                             square, &Square::changeColorOfSquare);

            x += size;
            if (x == 8 * size)
                x = 0;
        }
        y += size;
    }

    QColor brownColor(57, 38, 19);

    for (int i = 0; i < boardSize * 4; i++)
    {
        //left 0-7
        if (i < boardSize)
        {
            QGraphicsRectItem *rect = new QGraphicsRectItem();
            rect->setRect(squaresBoard[0]->rect().x() - sideBoardSize,
                          squaresBoard[0+8*i]->rect().y(),
                          sideBoardSize, size);

            scene->addItem(rect);

            rect->setBrush(brownColor);

            QGraphicsTextItem *text = new QGraphicsTextItem(rect);
            text->setPlainText(numbersBoard[7-i]);
            text->setScale(1.4);


            text->setPos(rect->boundingRect().left() + rect->boundingRect().width()/2 - text->boundingRect().width()/2,
                         rect->boundingRect().top() + rect->boundingRect().height()/2 - text->boundingRect().height()/2);

        }
        //bottom 8-15
        else if (i >= boardSize && i < 2*boardSize)
        {
            QGraphicsRectItem *rect = new QGraphicsRectItem();
            rect->setRect(squaresBoard[56+i-8]->rect().x(),
                          squaresBoard[56]->rect().bottom(),
                          size, sideBoardSize);

            scene->addItem(rect);

            rect->setBrush(brownColor);

            QGraphicsTextItem *text = new QGraphicsTextItem(rect);
            text->setPlainText(lettersBoard[i-8]);
            text->setScale(1.4);

            text->setPos(rect->boundingRect().left() + rect->boundingRect().width()/2 - text->boundingRect().width()/2,
                         rect->boundingRect().top() + rect->boundingRect().height()/2 - text->boundingRect().height()/2);
        }
        //right 16-23
        else if (i >= 2*boardSize && i < 3*boardSize)
        {
            QGraphicsRectItem *rect = new QGraphicsRectItem();
            rect->setRect(squaresBoard[7]->rect().right(),
                          squaresBoard[7+8*(i-16)]->rect().top(),
                          sideBoardSize, size);

            scene->addItem(rect);

            rect->setBrush(brownColor);

            QGraphicsTextItem *text = new QGraphicsTextItem(rect);
            text->setPlainText(numbersBoard[23-i]);
            text->setScale(1.4);

            text->setPos(rect->boundingRect().left() + rect->boundingRect().width()/2 - text->boundingRect().width()/2,
                         rect->boundingRect().top() + rect->boundingRect().height()/2 - text->boundingRect().height()/2);
        }
        //top 24-31
        else
        {
            QGraphicsRectItem *rect = new QGraphicsRectItem();
            rect->setRect(squaresBoard[0+i-24]->rect().x(),
                          squaresBoard[0]->rect().top() - sideBoardSize,
                          size, sideBoardSize);

            scene->addItem(rect);

            rect->setBrush(brownColor);

            QGraphicsTextItem *text = new QGraphicsTextItem(rect);
            text->setPlainText(lettersBoard[i-24]);
            text->setScale(1.4);

            text->setPos(rect->boundingRect().left() + rect->boundingRect().width()/2 - text->boundingRect().width()/2,
                         rect->boundingRect().top() + rect->boundingRect().height()/2 - text->boundingRect().height()/2);
        }

    }

    //top left corner
    QGraphicsRectItem *rectCornerTL = new QGraphicsRectItem();
    rectCornerTL->setRect(squaresBoard[0]->rect().left() - sideBoardSize,
                  squaresBoard[0]->rect().top() - sideBoardSize,
                  sideBoardSize, sideBoardSize);
    scene->addItem(rectCornerTL);
    rectCornerTL->setBrush(brownColor);

    //top right corner
    QGraphicsRectItem *rectCornerTR = new QGraphicsRectItem();
    rectCornerTR->setRect(squaresBoard[7]->rect().right(),
                  squaresBoard[7]->rect().top() - sideBoardSize,
                  sideBoardSize, sideBoardSize);
    scene->addItem(rectCornerTR);
    rectCornerTR->setBrush(brownColor);

    //bottom left corner
    QGraphicsRectItem *rectCornerBL = new QGraphicsRectItem();
    rectCornerBL->setRect(squaresBoard[56]->rect().left() - sideBoardSize,
                  squaresBoard[56]->rect().bottom(),
                  sideBoardSize, sideBoardSize);
    scene->addItem(rectCornerBL);
    rectCornerBL->setBrush(brownColor);

    //bottom right corner
    QGraphicsRectItem *rectCornerBR = new QGraphicsRectItem();
    rectCornerBR->setRect(squaresBoard[63]->rect().right(),
                  squaresBoard[63]->rect().bottom(),
                  sideBoardSize, sideBoardSize);
    scene->addItem(rectCornerBR);
    rectCornerBR->setBrush(brownColor);
}

void Display::setupPieces()
{
    // black
    squaresBoard[0]->setImage("/Users/jp/Desktop/dev/qt/projects/ChessGame/images/BlackRook.png");
    squaresBoard[1]->setImage("/Users/jp/Desktop/dev/qt/projects/ChessGame/images/BlackKnight.png");
    squaresBoard[2]->setImage("/Users/jp/Desktop/dev/qt/projects/ChessGame/images/BlackBishop.png");
    squaresBoard[3]->setImage("/Users/jp/Desktop/dev/qt/projects/ChessGame/images/BlackQueen.png");
    squaresBoard[4]->setImage("/Users/jp/Desktop/dev/qt/projects/ChessGame/images/BlackKing.png");
    squaresBoard[5]->setImage("/Users/jp/Desktop/dev/qt/projects/ChessGame/images/BlackBishop.png");
    squaresBoard[6]->setImage("/Users/jp/Desktop/dev/qt/projects/ChessGame/images/BlackKnight.png");
    squaresBoard[7]->setImage("/Users/jp/Desktop/dev/qt/projects/ChessGame/images/BlackRook.png");

    squaresBoard[8]->setImage("/Users/jp/Desktop/dev/qt/projects/ChessGame/images/BlackPawn.png");
    squaresBoard[9]->setImage("/Users/jp/Desktop/dev/qt/projects/ChessGame/images/BlackPawn.png");
    squaresBoard[10]->setImage("/Users/jp/Desktop/dev/qt/projects/ChessGame/images/BlackPawn.png");
    squaresBoard[11]->setImage("/Users/jp/Desktop/dev/qt/projects/ChessGame/images/BlackPawn.png");
    squaresBoard[12]->setImage("/Users/jp/Desktop/dev/qt/projects/ChessGame/images/BlackPawn.png");
    squaresBoard[13]->setImage("/Users/jp/Desktop/dev/qt/projects/ChessGame/images/BlackPawn.png");
    squaresBoard[14]->setImage("/Users/jp/Desktop/dev/qt/projects/ChessGame/images/BlackPawn.png");
    squaresBoard[15]->setImage("/Users/jp/Desktop/dev/qt/projects/ChessGame/images/BlackPawn.png");

    // white
    squaresBoard[48]->setImage("/Users/jp/Desktop/dev/qt/projects/ChessGame/images/WhitePawn.png");
    squaresBoard[49]->setImage("/Users/jp/Desktop/dev/qt/projects/ChessGame/images/WhitePawn.png");
    squaresBoard[50]->setImage("/Users/jp/Desktop/dev/qt/projects/ChessGame/images/WhitePawn.png");
    squaresBoard[51]->setImage("/Users/jp/Desktop/dev/qt/projects/ChessGame/images/WhitePawn.png");
    squaresBoard[52]->setImage("/Users/jp/Desktop/dev/qt/projects/ChessGame/images/WhitePawn.png");
    squaresBoard[53]->setImage("/Users/jp/Desktop/dev/qt/projects/ChessGame/images/WhitePawn.png");
    squaresBoard[54]->setImage("/Users/jp/Desktop/dev/qt/projects/ChessGame/images/WhitePawn.png");
    squaresBoard[55]->setImage("/Users/jp/Desktop/dev/qt/projects/ChessGame/images/WhitePawn.png");

    squaresBoard[56]->setImage("/Users/jp/Desktop/dev/qt/projects/ChessGame/images/WhiteRook.png");
    squaresBoard[57]->setImage("/Users/jp/Desktop/dev/qt/projects/ChessGame/images/WhiteKnight.png");
    squaresBoard[58]->setImage("/Users/jp/Desktop/dev/qt/projects/ChessGame/images/WhiteBishop.png");
    squaresBoard[59]->setImage("/Users/jp/Desktop/dev/qt/projects/ChessGame/images/WhiteQueen.png");
    squaresBoard[60]->setImage("/Users/jp/Desktop/dev/qt/projects/ChessGame/images/WhiteKing.png");
    squaresBoard[61]->setImage("/Users/jp/Desktop/dev/qt/projects/ChessGame/images/WhiteBishop.png");
    squaresBoard[62]->setImage("/Users/jp/Desktop/dev/qt/projects/ChessGame/images/WhiteKnight.png");
    squaresBoard[63]->setImage("/Users/jp/Desktop/dev/qt/projects/ChessGame/images/WhiteRook.png");
}

void Display::setStatusText(const QString& str)
{
    statusText->setPlainText(str);
}

void Display::setTurnText(const QString& str)
{
    turnText->setPlainText(str);
}

void Display::getResponseFromGame(QString response)
{
    std::string responseString = response.toStdString();

    // first click (choosing squareFrom)
    if (responseString == "Choosing piece")
    {
        statusText->setPlainText("");
        return;
    }

    if (responseString == "Not right turn")
    {
        statusText->setPlainText("Not right turn");
        return;
    }

    if (responseString == "Empty square selected")
    {
        statusText->setPlainText("Empty square selected");
        return;
    }

    if (responseString == "Check")
    {
        qDebug() << "Check";
        statusText->setPlainText("Check");
        return;
    }
    else if (responseString == "Invalid move")
    {
        qDebug() << "Invalid move";
        statusText->setPlainText("Invalid move");
        return;
    }
    else if (responseString == "Checkmate")
    {
        qDebug() << "Checkmate";
        statusText->setPlainText("Checkmate");
        return;
    }
    else if (responseString == "Stalemate")
    {
        qDebug() << "Stalemate";
        statusText->setPlainText("Stalemate");
        return;
    }
    // Otherwise, use the response from Game to move the correct pieces
    else
    {
        qDebug() << "Display got permission from Game to move icons.";
        qDebug() << "The response Game sent back was " << response;

        if (response == "White queenside castle")
        {
            qDebug() << "Display White queenside castle";
            QString tempRook = squaresBoard[56]->getPath();
            squaresBoard[56]->clearImage();
            squaresBoard[59]->setImage(tempRook);
        }
        else if (response == "White kingside castle")
        {
            qDebug() << "Display White kingside castle";
            QString tempRook = squaresBoard[63]->getPath();
            squaresBoard[63]->clearImage();
            squaresBoard[61]->setImage(tempRook);
        }
        else if (response == "Black queenside castle")
        {
            qDebug() << "Black queenside castle";
            QString tempRook = squaresBoard[0]->getPath();
            squaresBoard[0]->clearImage();
            squaresBoard[3]->setImage(tempRook);
        }
        else if (response == "Black kingside castle")
        {
            qDebug() << "Black kingside castle";
            QString tempRook = squaresBoard[7]->getPath();
            squaresBoard[7]->clearImage();
            squaresBoard[5]->setImage(tempRook);
        }
        else
        {
            QString squareFrom {""};
            QString squareTo {""};
            squareFrom += response[0];
            squareFrom += response[1];
            squareTo += response[2];
            squareTo += response[3];

            movesStrings.push_back(qMakePair(squareFrom, squareTo));

            QString tempImage;

            for (int i = 0; i < squaresBoard.size(); i++ )
            {
                if (squaresBoard[i]->getName() == squareFrom)
                {
                    tempImage = squaresBoard[i]->getPath();
                    squaresBoard[i]->clearImage();
                    break;
                }
            }
            for (int i = 0; i < squaresBoard.size(); i++ )
            {
                if (squaresBoard[i]->getName() == squareTo)
                {
                    squaresBoard[i]->setImage(tempImage);
                    break;
                }
            }

            if (turnColor == WHITE)
            {
                turnColor = BLACK;
                turnText->setPlainText("Black's Turn");
            }
            else
            {
                turnColor = WHITE;
                turnText->setPlainText("White's Turn");
            }
        }
    }

}

void Display::logMoves(QString move)
{

}

void Display::colorHelp(QString location)
{
    for (const auto &possibleLoc : game.searchPossibleMoves(location))
    {
        for (auto &square : squaresBoard)
        {
            if (possibleLoc == square->getName())
            {
                square->setColor(square->brush());
                QBrush brush(Qt::lightGray);
                square->setBrush(brush);
            }
        }
    }
}

void Display::clearPossibleMovesColor(QString locFrom, QString locTo)
{
    for (const auto &possibleLoc : game.searchPossibleMoves(locFrom))
    {
        for (auto &square : squaresBoard)
        {
            if (possibleLoc == square->getName())
            {
                square->clearColor(possibleLoc);
            }
        }
    }
}

Display::~Display()
{
    //delete ui;
}

QGraphicsScene* Display::getScene()
{
    return scene;
}

void Display::closingEvent(QCloseEvent *event){
    if(QMessageBox::question(this, "Quit?", "Do you really want to quit?",
                              QMessageBox::Yes | QMessageBox::No,
                              QMessageBox::No) == QMessageBox::Yes)
        event->accept();
    else
        event->ignore();
}

