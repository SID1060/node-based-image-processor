#ifndef OUTPUT_NODE_H
#define OUTPUT_NODE_H

#include <opencv2/core.hpp>

class OutputNode {
public:
    OutputNode(int id);
    int GetId() const;

    void SetInputImage(const cv::Mat& img); // External update method
    void Render();

private:
    int id_;
    cv::Mat image_;
    unsigned int textureID_;
    int quality_;
    bool imageAvailable_;

    void UploadTexture();
    void SaveImage();
};

#endif
