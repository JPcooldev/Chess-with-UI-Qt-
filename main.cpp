#include "display.h"

#include <QApplication>
#include <QGraphicsView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Display display;
    QGraphicsView view(display.getScene());
    view.show();
    return a.exec();
}
