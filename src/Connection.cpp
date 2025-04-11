#include "Connection.h"
#include "NodeBox.h"
#include <QPen>

Connection::Connection(NodeBox* from, NodeBox* to)
    : fromNode(from), toNode(to) {
    setZValue(-1);  // behind the nodes
    updatePosition();
}

QRectF Connection::boundingRect() const {
    return QRectF(line().p1(), line().p2()).normalized();
}

void Connection::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setPen(QPen(Qt::green, 2));
    painter->drawLine(line());
}

void Connection::updatePosition() {
    if (fromNode && toNode) {
        QLineF newLine(fromNode->sceneBoundingRect().center(),
                       toNode->sceneBoundingRect().center());
        setLine(newLine);
    }
}

