#pragma once

#include <QGraphicsLineItem>
#include <QPainter>

class NodeBox;

class Connection : public QGraphicsLineItem {
public:
    Connection(NodeBox* from, NodeBox* to);

    void updatePosition();

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    QRectF boundingRect() const override;

private:
    NodeBox* fromNode;
    NodeBox* toNode;
};

