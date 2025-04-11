#include "BrightnessContrastNode.h"
#include <QPainter>
#include <opencv2/opencv.hpp>

BrightnessContrastNode::BrightnessContrastNode() {
    setFlags(ItemIsMovable | ItemIsSelectable);
}

void BrightnessContrastNode::setInputImage(const QImage& image) {
    inputImage = image;
    updateImage();
    update();
}

void BrightnessContrastNode::setBrightness(int value) {
    brightness = value;
    updateImage();
    update();
}

void BrightnessContrastNode::setContrast(double value) {
    contrast = value;
    updateImage();
    update();
}

void BrightnessContrastNode::updateImage() {
    if (inputImage.isNull()) return;

    cv::Mat mat = cv::Mat(inputImage.height(), inputImage.width(), CV_8UC4, const_cast<uchar*>(inputImage.bits()), inputImage.bytesPerLine());
    cv::Mat result;

    mat.convertTo(result, -1, contrast, brightness);
    QImage out(result.data, result.cols, result.rows, result.step, QImage::Format_RGBA8888);
    processedImage = out.copy();  // deep copy
}

QImage BrightnessContrastNode::getProcessedImage() const {
    return processedImage;
}

void BrightnessContrastNode::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    painter->setBrush(Qt::darkMagenta);
    painter->drawRect(boundingRect());
    painter->setPen(Qt::white);
    painter->drawText(boundingRect(), Qt::AlignTop | Qt::AlignHCenter, "Brightness/Contrast");

    if (!processedImage.isNull()) {
        QRect target = QRect(10, 20, 80, 50);
        QImage scaled = processedImage.scaled(target.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        painter->drawImage(target.topLeft(), scaled);
    }
}
