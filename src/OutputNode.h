#ifndef OUTPUT_NODE_H
#define OUTPUT_NODE_H

#include <opencv2/opencv.hpp>
#include <string>

class OutputNode {
public:
    OutputNode(int id);
    void Render();
    void SetInputImage(const cv::Mat& img);

private:
    int id_;
    cv::Mat image_;
    std::string savePath_;
    int quality_ = 95;
    bool imageAvailable_ = false;

    void SaveImage();
};

#endif
