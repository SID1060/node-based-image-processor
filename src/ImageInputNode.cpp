#include "ImageInputNode.h"
#include <QPainter>
#include <QFileInfo>

ImageInputNode::ImageInputNode() {
    setFlags(ItemIsMovable | ItemIsSelectable);
}

void ImageInputNode::setImage(const QString& filePath) {
    path = filePath;
    image.load(filePath);
    update();
}

QImage ImageInputNode::getImage() const {
    return image;
}

QString ImageInputNode::getMetadata() const {
    if (image.isNull()) return "No image loaded.";
    QFileInfo info(path);
    return QString("File: %1\nSize: %2 x %3\nFormat: %4\nBytes: %5")
        .arg(info.fileName())
        .arg(image.width())
        .arg(image.height())
        .arg(image.format())
        .arg(info.size());
}

void ImageInputNode::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    painter->setBrush(Qt::darkBlue);
    painter->drawRect(boundingRect());
    painter->setPen(Qt::white);
    painter->drawText(boundingRect(), Qt::AlignTop | Qt::AlignHCenter, "Image Input");

    if (!image.isNull()) {
        QRect target = QRect(10, 20, 80, 50); // preview area
        QImage scaled = image.scaled(target.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        painter->drawImage(target.topLeft(), scaled);
    }
}