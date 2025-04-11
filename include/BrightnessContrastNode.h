#pragma once

#include "NodeBox.h"
#include <QImage>

class BrightnessContrastNode : public NodeBox {
    Q_OBJECT

public:
    BrightnessContrastNode();

    void setInputImage(const QImage& image);
    QImage getProcessedImage() const;

    void setBrightness(int value);  // -100 to +100
    void setContrast(double value); // 0.0 to 3.0

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QImage inputImage;
    QImage processedImage;

    int brightness = 0;
    double contrast = 1.0;

    void updateImage();
};
