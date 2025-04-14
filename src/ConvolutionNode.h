#ifndef CONVOLUTION_NODE_H
#define CONVOLUTION_NODE_H

#include <opencv2/opencv.hpp>
#include <array>
#include <string>

class ConvolutionNode {
public:
    ConvolutionNode(int id);
    int GetId() const { return id_; }

    void SetInputImage(const cv::Mat& img);
    const cv::Mat& GetOutputImage() const;

    void Render();

private:
    int id_;
    cv::Mat inputImage_, outputImage_;
    int kernelSize_ = 3;
    std::array<float, 25> kernel_;
    bool kernelChanged_ = true;

    void ApplyKernel();
    void SetPreset(const std::string& name);
};

#endif
