#include "square.h"

#include <QBrush>
#include <QDebug>
//#include <QColor>

Square::Square(int xcoord, int ycoord, int size)
{
    this->xcoord = xcoord;
    this->ycoord = ycoord;
    this->size = size;
    setRect(xcoord, ycoord, size, size);
    squareImage.setParentItem(this);
}

void Square::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        color = this->brush();
        QBrush brush(Qt::red);
        setBrush(brush);
        qDebug() << "You clicked " << this->name;
    }
    emit clicked(this->name);
}

void Square::setImage(QString path)
{
    this->path = path;
    squareImage.setPixmap(path);
    squareImage.setPos(xcoord + size/2 - squareImage.pixmap().width()/2,
                       ycoord + size/2 - squareImage.pixmap().height()/2);
    squareImage.show();
}

QString Square::getPath() const
{
    return path;
}

void Square::setName(QString name)
{
    this->name = name;
}

QString Square::getName() const
{
    return name;
}

void Square::clearImage()
{
    squareImage.hide();
}

void Square::clearColor(QString location)
{
    if (location == name)
    {
        qDebug() << "clearColor " << name;
        setBrush(color);
    }
}

void Square::setColor(QBrush color)
{
    this->color = color;
}




