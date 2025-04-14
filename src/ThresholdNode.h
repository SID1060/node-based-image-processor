#ifndef THRESHOLD_NODE_H
#define THRESHOLD_NODE_H

#include <opencv2/opencv.hpp>

class ThresholdNode {
public:
    ThresholdNode(int id);
    int GetId() const { return id_; }

    void SetInputImage(const cv::Mat& img);
    const cv::Mat& GetOutputImage() const;

    void Render();

private:
    int id_;
    cv::Mat inputImage_;
    cv::Mat outputImage_;
    int thresholdType_; // 0 = Binary, 1 = Otsu, 2 = Adaptive
    float threshValue_;
    float maxValue_;
    int adaptiveMethod_; // 0 = Mean, 1 = Gaussian

    void ApplyThreshold();
    void DrawHistogram(const cv::Mat& gray);
};

#endif

