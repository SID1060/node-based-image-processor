#ifndef BLUR_NODE_H
#define BLUR_NODE_H

#include <opencv2/opencv.hpp>
#include <string>

class BlurNode {
public:
    BlurNode(int id);
    int GetId() const;

    void SetInputImage(const cv::Mat& img);
    const cv::Mat& GetOutputImage() const;
    void Render();

private:
    int id_;
    int radius_;
    bool directional_;  // true = horizontal, false = uniform
    cv::Mat inputImage_;
    cv::Mat outputImage_;

    void ApplyBlur();
    void ShowKernelPreview();
};

#endif // BLUR_NODE_H
