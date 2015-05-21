#ifndef ARROW_H
#define ARROW_H

#include <QGraphicsLineItem>
#include <QLineF>
#include <QGraphicsItem>
#include "diagramitem.h"
#include "diagramtextitem.h"
#include "relacja.h"

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

    enum ArrowType
    {
        Generalization,
        Dependency,
        Composition,
        Aggregation,
        Association
    };

    Arrow(DiagramTextItem *startItem, DiagramTextItem *endItem,ArrowType type, QGraphicsItem *parent = 0);
    ~Arrow();

    int type() const { return Type; }
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paintArrowHead(QPainter *painter);
    void setColor(const QColor &color) { myColor = color; }
    DiagramTextItem *startItem() const { return myStartItem; }
    DiagramTextItem *endItem() const { return myEndItem; }
    void pozycjaPrzesunietaDoSrodka(QPoint& startElem, QPoint& endElem);
    void updatePosition();
    Rel::Relacja *getRelacjaAdres();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0);

private:
    Rel::Relacja* relacja;
    DiagramTextItem *myStartItem;
    DiagramTextItem *myEndItem;
    ArrowType myArrowType;
    QColor myColor;
    QPolygonF arrowHead;
};

#endif
