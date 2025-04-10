#include "NodeBox.h"
#include <QPainter>

NodeBox::NodeBox() {
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
}

QRectF NodeBox::boundingRect() const {
    return QRectF(0, 0, 100, 50);  // width x height
}

void NodeBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(Qt::darkGray);
    painter->drawRect(boundingRect());
    painter->setPen(Qt::white);
    painter->drawText(boundingRect(), Qt::AlignCenter, "Node");
}

void NodeBox::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    m_lastPos = event->pos();
    QGraphicsItem::mousePressEvent(event);
}

void NodeBox::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem::mouseMoveEvent(event);
}
