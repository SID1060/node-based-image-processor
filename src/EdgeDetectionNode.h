#ifndef EDGE_DETECTION_NODE_H
#define EDGE_DETECTION_NODE_H

#include <opencv2/opencv.hpp>

class EdgeDetectionNode {
public:
    EdgeDetectionNode(int id);
    int  GetId() const { return id_; }

    void SetInputImage(const cv::Mat& img);
    const cv::Mat& GetOutputImage() const { return outputImage_; }
    void Render();

private:
    int id_;
    cv::Mat inputImage_;
    cv::Mat outputImage_;

    // 0 = Sobel, 1 = Canny
    int algorithmType_ = 0;

    // Sobel params
    int sobelKernel_ = 3;      // must be odd: 1,3,5,7...
    bool sobelX_ = true;
    bool sobelY_ = true;

    // Canny params (now float!)
    float cannyThresh1_ = 50.0f;
    float cannyThresh2_ = 150.0f;
    int   cannyAperture_ = 3;  // 3,5,7

    // Overlay
    bool overlay_ = false;

    void ApplyEdgeDetection();
};

#endif // EDGE_DETECTION_NODE_H
