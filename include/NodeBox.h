#ifndef NODEBOX_H
#define NODEBOX_H

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

class NodeBox : public QGraphicsItem {
public:
    NodeBox();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QPointF m_lastPos;
};

#endif // NODEBOX_H
