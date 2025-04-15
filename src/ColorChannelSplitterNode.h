#ifndef COLOR_CHANNEL_SPLITTER_NODE_H
#define COLOR_CHANNEL_SPLITTER_NODE_H

#include <opencv2/opencv.hpp>
#include <array>

class ColorChannelSplitterNode {
public:
    ColorChannelSplitterNode(int id);
    int GetId() const { return id_; }

    void SetInputImage(const cv::Mat& img);
    const cv::Mat& GetChannelImage(int channel) const;
    void Render();

private:
    int id_;
    cv::Mat inputImage_;
    cv::Mat lastInput_;                 // Used for reference (optional)
    std::array<cv::Mat, 4> channels_;
    cv::Scalar lastHash_;              // Used to detect changes efficiently
    bool grayscale_ = false;
};

#endif // COLOR_CHANNEL_SPLITTER_NODE_H