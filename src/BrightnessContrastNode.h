#ifndef BRIGHTNESS_CONTRAST_NODE_H
#define BRIGHTNESS_CONTRAST_NODE_H

#include <opencv2/opencv.hpp>

class BrightnessContrastNode {
public:
    BrightnessContrastNode(int id);
    int  GetId() const { return id_; }
    void SetInputImage(const cv::Mat& img);
    const cv::Mat& GetOutputImage() const { return outputImage_; }
    void Render();

private:
    int id_;
    cv::Mat inputImage_;
    cv::Mat outputImage_;
    int brightness_ = 0;     // -100..+100
    float contrast_ = 1.0f;  //  0..3
};

#endif
