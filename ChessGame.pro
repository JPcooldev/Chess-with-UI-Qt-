QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Chess/Bishop.cpp \
    Chess/Chessboard.cpp \
    Chess/Game.cpp \
    Chess/King.cpp \
    Chess/Knight.cpp \
    Chess/Pawn.cpp \
    Chess/Piece.cpp \
    Chess/Queen.cpp \
    Chess/Rook.cpp \
    main.cpp \
    display.cpp \
    square.cpp

HEADERS += \
    Chess/Bishop.hpp \
    Chess/Chessboard.hpp \
    Chess/Game.hpp \
    Chess/King.hpp \
    Chess/Knight.hpp \
    Chess/Pawn.hpp \
    Chess/Piece.hpp \
    Chess/Queen.hpp \
    Chess/Rook.hpp \
    Chess/typedef.h \
    display.h \
    square.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/BlackBishop.png \
    images/BlackKing.png \
    images/BlackKnight.png \
    images/BlackPawn.png \
    images/BlackQueen.png \
    images/BlackRook.png \
    images/WhiteBishop.png \
    images/WhiteKing.png \
    images/WhiteKnight.png \
    images/WhitePawn.png \
    images/WhiteQueen.png \
    images/WhiteRook.png \
    images/welcomePageImage.png
