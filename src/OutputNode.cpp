#include "OutputNode.h"
#include <QPainter>

OutputNode::OutputNode() {
    setFlags(ItemIsMovable | ItemIsSelectable);
}

void OutputNode::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    painter->setBrush(Qt::darkBlue);
    painter->drawRect(boundingRect());
    painter->setPen(Qt::white);
    painter->drawText(boundingRect(), Qt::AlignCenter, "Output Node");
}

