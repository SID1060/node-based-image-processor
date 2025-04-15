// #ifndef BLEND_NODE_H
// #define BLEND_NODE_H

// #include <opencv2/opencv.hpp>
// #include <string>

// class BlendNode {
// public:
//     BlendNode(int id);
//     void Render();
//     void SetInputA(const cv::Mat& img);
//     void SetInputB(const cv::Mat& img);
//     const cv::Mat& GetBlendedImage() const;

// private:
//     int id_;
//     cv::Mat imageA_;
//     cv::Mat imageB_;
//     cv::Mat blended_;
//     float opacity_ = 0.5f;
//     int blendMode_ = 0;

//     void BlendImages();
// };

// #endif

// #ifndef BLEND_NODE_H
// #define BLEND_NODE_H

// #include <opencv2/opencv.hpp>

// class BlendNode {
// public:
//     BlendNode(int id);
//     int  GetId() const { return id_; }

//     // Called by the graph evaluator to set both inputs
//     void SetInputImages(const cv::Mat& imgA, const cv::Mat& imgB);
//     // Returns the blended result
//     cv::Mat GetOutputImage() const { return outputImage_; }

//     // Renders the node UI
//     void Render();

// private:
//     int id_;
//     int inputAttrA_, inputAttrB_, outputAttr_;

//     cv::Mat imageA_, imageB_, outputImage_;

//     // Blend parameters
//     int   mode_    = 0;    // 0=Normal,1=Multiply,2=Screen,3=Overlay,4=Difference
//     float opacity_ = 0.5f; // mix factor of second image

//     // Compute the blended image
//     void ApplyBlend();
// };

// #endif // BLEND_NODE_H

// BlendNode.h
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
    void LoadImageB(const std::string& path); // Add this method

private:
    int id_;
    cv::Mat imageA_, imageB_, blended_;
    int blendMode_; // 0 = Add, 1 = Multiply, 2 = Average
    float opacity_;
    bool imageAvailable_;
    unsigned int textureID_;

    void BlendImages();
    void UploadTexture();
};

#endif