#ifndef DIAGRAMITEM_H
#define DIAGRAMITEM_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPolygonF>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QList>

class QPixmap;
class QGraphicsItem;
class QGraphicsScene;
class QTextEdit;
class QGraphicsSceneMouseEvent;
class QMenu;
class QGraphicsSceneContextMenuEvent;
class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;
class QPolygonF;

class Arrow;

class DiagramItem : public QGraphicsPolygonItem
{
public:
    enum { Type = UserType + 15 };
    // ściśle zabronione specyfikować poszczególne liczby dla poniższej struktury
    // Jeżeli dodajemy nowy element do struktury to nie na koniec ani na początek!
    enum DiagramType {Class, Struct, Namespace, Enum, Union};

    DiagramItem(DiagramType diagramType, QMenu *contextMenu,
        QGraphicsItem *parent = 0);

    void removeArrow(Arrow *arrow);
    void removeArrows();
    DiagramType diagramType() const
        { return myDiagramType; }
    QPolygonF polygon() const
        { return myPolygon; }
    void addArrow(Arrow *arrow);
    QPixmap image() const;
    QString textForButton();
    int type() const
        { return Type;}

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    DiagramType myDiagramType;
    QPolygonF myPolygon;
    QMenu *myContextMenu;
    QList<Arrow *> arrows;
};

#endif
