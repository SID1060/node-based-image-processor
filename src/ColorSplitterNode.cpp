#include "ColorSplitterNode.h"
#include <QPainter>

ColorSplitterNode::ColorSplitterNode() {
    setFlags(ItemIsMovable | ItemIsSelectable);
}

void ColorSplitterNode::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    painter->setBrush(Qt::darkGreen);
    painter->drawRect(boundingRect());
    painter->setPen(Qt::white);
    painter->drawText(boundingRect(), Qt::AlignCenter, "Color Splitter Node");
}
