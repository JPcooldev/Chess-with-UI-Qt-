#ifndef SQUARE_H
#define SQUARE_H

#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QString>
#include <QBrush>

class Square : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

    QString name;
    int xcoord, ycoord;
    int size;
    QString path;
    QGraphicsPixmapItem squareImage;
    QBrush color;
public:
    Square(int xcoord, int ycoord, int size);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    QString getName() const;
    void setImage(QString path);
    QString getPath() const;
    void setName(QString name);
    void clearImage();
    void setColor(QBrush color);
signals:
    void clicked(QString position);
public slots:
    void clearColor(QString location);
};

#endif // SQUARE_H
