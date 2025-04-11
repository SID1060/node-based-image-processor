#pragma once
#include "NodeBox.h"

class ColorSplitterNode : public NodeBox {
    Q_OBJECT
public:
    ColorSplitterNode();
protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
};
