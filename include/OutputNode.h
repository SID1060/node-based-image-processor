#pragma once
#include "NodeBox.h"

class OutputNode : public NodeBox {
    Q_OBJECT
public:
    OutputNode();
protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
};

