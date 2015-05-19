#ifndef DIAGRAMTEXTITEM_H
#define DIAGRAMTEXTITEM_H

#include <QGraphicsTextItem>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QString>
#include <QPen>
#include <QPainter>
#include <QMenu>
#include <QList>
#include <QGraphicsSceneContextMenuEvent>
#include "arrow.h"
#include "element.h"


class QFocusEvent;
class QGraphicsItem;
class QGraphicsScene;
class QGraphicsSceneMouseEvent;

class DiagramTextItem : public QGraphicsTextItem
{
    Q_OBJECT

public:
    enum { Type = UserType + 3 };
    enum DiagramTextType {Class, Struct, Namespace, Enum, Union};

    DiagramTextItem(DiagramTextType diagramType, QGraphicsItem *parent = 0);

    int type() const{ return Type; }
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);
    QRectF boundingRect() const;
    void removeArrow(Arrow *arrow);
    void removeArrows();
    void addArrow(Arrow *arrow);
    void setMenu(QMenu *menu);
    DiagramTextType diagramType() const { return myDiagramType; }
    QString textForButton();

signals:
    void lostFocus(DiagramTextItem *item);
    void selectedChange(QGraphicsItem *item);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void focusOutEvent(QFocusEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

private:
    DiagramTextType myDiagramType;
    Element* element;
    QMenu *myContextMenu;
    QList<Arrow *> arrows;
};

#endif
