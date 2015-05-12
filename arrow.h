#ifndef ARROW_H
#define ARROW_H

#include <QGraphicsLineItem>
#include <QLineF>
#include <QGraphicsItem>
#include "diagramitem.h"
#include "diagramtextitem.h"

class QGraphicsPolygonItem;
class QGraphicsLineItem;
class QGraphicsScene;
class QRectF;
class QGraphicsSceneMouseEvent;
class QPainterPath;
class DiagramTextItem;

class Arrow : public QGraphicsLineItem
{
public:
    enum { Type = UserType + 4 };

    Arrow(DiagramTextItem *startItem, DiagramTextItem *endItem, QGraphicsItem *parent = 0);

    int type() const { return Type; }
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void setColor(const QColor &color) { myColor = color; }
    DiagramTextItem *startItem() const { return myStartItem; }
    DiagramTextItem *endItem() const { return myEndItem; }
    void pozycjaPrzesunietaDoSrodka(QPoint& startElem, QPoint& endElem);
    void updatePosition();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0);

private:
    DiagramTextItem *myStartItem;
    DiagramTextItem *myEndItem;
    QColor myColor;
    QPolygonF arrowHead;
};

#endif
