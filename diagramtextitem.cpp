#include <QtGui>

#include "diagramtextitem.h"
#include "diagramscene.h"

DiagramTextItem::DiagramTextItem(DiagramTextType diagramType, QGraphicsItem *parent)
    : QGraphicsTextItem(parent)
{
    myDiagramType = diagramType;
    //myContextMenu = contextMenu;
    myContextMenu = NULL;

    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

void DiagramTextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsTextItem::paint(painter,option,widget);
    painter->setPen(Qt::black);
    painter->drawRect(boundingRect());
}

QRectF DiagramTextItem::boundingRect() const
{
    return QGraphicsTextItem::boundingRect().adjusted(-2,-2,+2,+2);
}

void DiagramTextItem::removeArrow(Arrow *arrow)
{
    int index = arrows.indexOf(arrow);

    if (index != -1)
        arrows.removeAt(index);
}

void DiagramTextItem::removeArrows()
{
    foreach (Arrow *arrow, arrows) {
        arrow->startItem()->removeArrow(arrow);
        arrow->endItem()->removeArrow(arrow);
        scene()->removeItem(arrow);
        delete arrow;
    }
}

void DiagramTextItem::addArrow(Arrow *arrow)
{
    arrows.append(arrow);
}

void DiagramTextItem::setMenu(QMenu *menu)
{
    myContextMenu = menu;
}

QString DiagramTextItem::textForButton()
{
    QString Product;

    switch(myDiagramType)
    {
    case Class:
        Product = "Class";
        break;
    case Struct:
        Product = "Struct";
        break;
    case Namespace:
        Product = "Namespace";
        break;
    case Union:
        Product = "Union";
        break;
    case Enum:
        Product = "Enum";
        break;
    }

    return Product;
}

QVariant DiagramTextItem::itemChange(GraphicsItemChange change,
                     const QVariant &value)
{
    if (change == QGraphicsItem::ItemSelectedHasChanged)
        emit selectedChange(this);
    return value;
}

void DiagramTextItem::focusOutEvent(QFocusEvent *event)
{
    setTextInteractionFlags(Qt::NoTextInteraction);
    emit lostFocus(this);
    QGraphicsTextItem::focusOutEvent(event);
}

void DiagramTextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (textInteractionFlags() == Qt::NoTextInteraction)
        setTextInteractionFlags(Qt::TextEditorInteraction);
    QGraphicsTextItem::mouseDoubleClickEvent(event);
}

void DiagramTextItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    myContextMenu->exec(event->screenPos());
}

