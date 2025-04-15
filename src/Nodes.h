#ifndef NODES_H
#define NODES_H

#include <opencv2/opencv.hpp>
#include <string>

class ImageInputNode {
public:
    ImageInputNode(int id);
    void Render();
    int GetId() const { return id_; }
    const cv::Mat& GetImage() const { return image_; } // Return const reference
    bool IsImageLoaded() const { return imageLoaded_; }

private:
    int id_;
    cv::Mat image_;
    std::string imagePath_;
    bool imageLoaded_ = false;

    void LoadImage(const std::string& path);
};

#endif