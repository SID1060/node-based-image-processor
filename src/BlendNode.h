#ifndef BLEND_NODE_H
#define BLEND_NODE_H

#include <opencv2/core.hpp>
#include <string>

class BlendNode {
public:
    BlendNode(int id);
    int GetId() const;

    void SetInputImageA(const cv::Mat& img);
    void SetInputImageB(const cv::Mat& img);
    cv::Mat GetBlendedImage() const;

    void Render();
    bool HasBothInputs() const;
    void LoadImageB(const std::string& path);

private:
    int id_;
    cv::Mat imageA_, imageB_, blended_, preview_;
    int blendMode_; // 0 = Add, 1 = Multiply, 2 = Average
    float opacity_;
    bool imageAvailable_;
    unsigned int textureID_;
    bool needsUpdate_; // Flag to trigger blending

    void BlendImages();
    void UploadTexture();
    void UpdatePreview();
};

#endif