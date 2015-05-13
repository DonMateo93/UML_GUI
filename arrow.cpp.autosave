#include <QtGui>

#include "arrow.h"
#include <math.h>
#include <QTransform>

const qreal Pi = 3.14;

Arrow::Arrow(DiagramTextItem *startItem, DiagramTextItem *endItem, ArrowType type, QGraphicsItem *parent)
    : QGraphicsLineItem(parent)
{
    myStartItem = startItem;
    myEndItem = endItem;
    myArrowType = type;
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    myColor = Qt::black;

    if(myArrowType == Dependency)
        setPen(QPen(myColor, 2, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
    else
        setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

QRectF Arrow::boundingRect() const
{
    qreal extra = (pen().width() + 20) / 2.0;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

QPainterPath Arrow::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(arrowHead);
    return path;
}

void Arrow::paintArrowHead(QPainter* painter)
{
    qreal arrowSize = 20;
    double angle = ::acos(line().dx() / line().length());
    if (line().dy() >= 0)
        angle = (Pi * 2) - angle;

    QPointF arrowP1 = line().p1() + QPointF(sin(angle + Pi / 3) * arrowSize,
                                            cos(angle + Pi / 3) * arrowSize);
    QPointF arrowP2 = line().p1() + QPointF(sin(angle + Pi - Pi / 3) * arrowSize,
                                            cos(angle + Pi - Pi / 3) * arrowSize);

    QLineF IntersectLine(arrowP1,arrowP2);
    QPointF pPrzeciecia;
    IntersectLine.intersect(line(),&pPrzeciecia);
    QLineF liniaOdleglosc(pPrzeciecia,line().p1());
    QPointF pDlaRombu = line().p1() - pPrzeciecia;
    pDlaRombu = line().p1() - 2*pDlaRombu;

    QBrush brusz;
    switch(myArrowType)
    {
    case Generalization:
        arrowHead.clear();
        arrowHead << line().p1() << arrowP1 << arrowP2;
        painter->drawLine(line());
        brusz.setColor(Qt::white);
        painter->setBrush(brusz);
        painter->drawPolygon(arrowHead);
        brusz.setColor(Qt::black);
        painter->setBrush(brusz);
        break;

    case Dependency:
        painter->drawLine(line());
        painter->drawLine(line().p1(),arrowP1);
        painter->drawLine(line().p1(),arrowP2);
        break;

    case Composition:
        arrowHead.clear();
        arrowHead << line().p1() << arrowP1 << pDlaRombu << arrowP2;
        painter->drawLine(line());
        painter->drawPolygon(arrowHead);
        break;

    case Aggregation:
        arrowHead.clear();
        arrowHead << line().p1() << arrowP1 << pDlaRombu << arrowP2;
        painter->drawLine(line());
        brusz.setColor(Qt::white);
        painter->setBrush(brusz);
        painter->drawPolygon(arrowHead);
        brusz.setColor(Qt::black);
        painter->setBrush(brusz);
        break;

    case Association:
        painter->drawLine(line());
        painter->drawLine(line().p1(),arrowP1);
        painter->drawLine(line().p1(),arrowP2);
        break;
    }
}

void Arrow::pozycjaPrzesunietaDoSrodka(QPoint &startElem, QPoint &endElem)
{
    QTransform transform;
    QPolygon polygon = transform.mapToPolygon(myEndItem->boundingRect().toRect());
    QPoint p1 = polygon.at(0);
    QPoint p2 = polygon.at(0);

    QPoint observer1 = mapFromItem(myStartItem, 0, 0).toPoint();
    QPoint observer2 = mapFromItem(myEndItem, 0, 0).toPoint();

    foreach(QPoint pomoc, polygon)
    {
        if(p1.x() < pomoc.x())
            p1.setX(pomoc.x());

        if(p1.y() < pomoc.y())
            p1.setY(pomoc.y());

        if(p2.x() > pomoc.x())
            p2.setX(pomoc.x());

        if(p2.y() > pomoc.y())
            p2.setY(pomoc.y());
    }

    polygon = transform.mapToPolygon(myStartItem->boundingRect().toRect());
    QPoint p3 = polygon.at(0);
    QPoint p4 = polygon.at(0);

    foreach(QPoint pomoc, polygon)
    {
        if(p3.x() < pomoc.x())
            p3.setX(pomoc.x());

        if(p3.y() < pomoc.y())
            p3.setY(pomoc.y());

        if(p4.x() > pomoc.x())
            p4.setX(pomoc.x());

        if(p4.y() > pomoc.y())
            p4.setY(pomoc.y());
    }

    double liczbax = (p3.x() - p4.x())/2;
    double liczbay = (p3.y() - p4.y())/2;
    startElem.setX(observer1.x() + liczbax);
    startElem.setY(observer1.y() + liczbay);
    double liczbax2 = (p1.x() - p2.x())/2;
    double liczbay2 = (p1.y() - p2.y())/2;
    endElem.setX(observer2.x() + liczbax2);
    endElem.setY(observer2.y() + liczbay2);
}

void Arrow::updatePosition()
{
    QTransform transform;
    QPolygon polygon = transform.mapToPolygon(myEndItem->boundingRect().toRect());
    QPoint p1 = polygon.at(0);
    QPoint p2 = polygon.at(0);

    QPoint observer1 = mapFromItem(myStartItem, 0, 0).toPoint();
    QPoint observer2 = mapFromItem(myEndItem, 0, 0).toPoint();

    foreach(QPoint pomoc, polygon)
    {
        if(p1.x() < pomoc.x())
            p1.setX(pomoc.x());

        if(p1.y() < pomoc.y())
            p1.setY(pomoc.y());

        if(p2.x() > pomoc.x())
            p2.setX(pomoc.x());

        if(p2.y() > pomoc.y())
            p2.setY(pomoc.y());
    }

    polygon = transform.mapToPolygon(myStartItem->boundingRect().toRect());
    QPoint p3 = polygon.at(0);
    QPoint p4 = polygon.at(0);

    foreach(QPoint pomoc, polygon)
    {
        if(p3.x() < pomoc.x())
            p3.setX(pomoc.x());

        if(p3.y() < pomoc.y())
            p3.setY(pomoc.y());

        if(p4.x() > pomoc.x())
            p4.setX(pomoc.x());

        if(p4.y() > pomoc.y())
            p4.setY(pomoc.y());
    }

    double liczbax = (p3.x() - p4.x())/2;
    double liczbay = (p3.y() - p4.y())/2;
    QPoint pStart(observer1.x() + liczbax,observer1.y() + liczbay);

    double liczbax2 = (p1.x() - p2.x())/2;
    double liczbay2 = (p1.y() - p2.y())/2;
    QPoint pEnd(observer2.x() + liczbax2,observer2.y() + liczbay2);

    QLineF line(pStart, pEnd);
    setLine(line);

}

void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *,QWidget *)
{
    if (myStartItem->collidesWithItem(myEndItem))
        return;

    QPen myPen = pen();
    myPen.setColor(myColor);
    qreal arrowSize = 20;
    painter->setPen(myPen);
    painter->setBrush(myColor);

    QPoint startElem,endElem;
    pozycjaPrzesunietaDoSrodka(startElem,endElem);

    QLineF centerLine(startElem, endElem);
    QTransform transform;
    QPolygon polygon = transform.mapToPolygon(myEndItem->boundingRect().toRect());
    QPolygonF endPolygon = polygon;
    QPointF p1 = endPolygon.first() + endElem;
    QPointF p2;
    QPointF intersectPoint;
    QLineF polyLine;
    for (int i = 1; i < endPolygon.count(); ++i) {
    p2 = endPolygon.at(i) + endElem;
    polyLine = QLineF(p1, p2);
    QLineF::IntersectType intersectType =
        polyLine.intersect(centerLine, &intersectPoint);
    if (intersectType == QLineF::BoundedIntersection)
        break;
        p1 = p2;
    }

    setLine(QLineF(intersectPoint, startElem));

    double angle = ::acos(line().dx() / line().length());
    if (line().dy() >= 0)
        angle = (Pi * 2) - angle;

        QPointF arrowP1 = line().p1() + QPointF(sin(angle + Pi / 3) * arrowSize,
                                        cos(angle + Pi / 3) * arrowSize);
        QPointF arrowP2 = line().p1() + QPointF(sin(angle + Pi - Pi / 3) * arrowSize,
                                        cos(angle + Pi - Pi / 3) * arrowSize);

//        arrowHead.clear();
//        arrowHead << line().p1() << arrowP1 << arrowP2;
//        painter->drawLine(line());
//        painter->drawPolygon(arrowHead);
        paintArrowHead(painter);
        if (isSelected()) {
            painter->setPen(QPen(myColor, 1, Qt::DashLine));
        QLineF myLine = line();
        myLine.translate(0, 4.0);
        painter->drawLine(myLine);
        myLine.translate(0,-8.0);
        painter->drawLine(myLine);
    }
}

