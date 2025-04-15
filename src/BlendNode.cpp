// #include "BlendNode.h"
// #include <imgui.h>
// #include <imnodes.h>

// BlendNode::BlendNode(int id) : id_(id) {}

// void BlendNode::SetInputA(const cv::Mat& img) {
//     imageA_ = img.clone();
//     BlendImages();
// }

// void BlendNode::SetInputB(const cv::Mat& img) {
//     imageB_ = img.clone();
//     BlendImages();
// }

// const cv::Mat& BlendNode::GetBlendedImage() const {
//     return blended_;
// }

// void BlendNode::BlendImages() {
//     if (imageA_.empty() || imageB_.empty()) return;

//     cv::Mat a, b;
//     cv::resize(imageB_, b, imageA_.size());
//     a = imageA_;

//     switch (blendMode_) {
//         case 0: // Normal blend (linear interpolation)
//             cv::addWeighted(a, 1.0f - opacity_, b, opacity_, 0.0, blended_);
//             break;
//         case 1: // Multiply
//             cv::multiply(a, b, blended_, 1.0 / 255);
//             break;
//         case 2: // Screen
//             blended_ = 255 - ((255 - a).mul(255 - b) / 255);
//             break;
//         case 3: // Overlay
//             blended_ = cv::Mat::zeros(a.size(), a.type());
//             for (int y = 0; y < a.rows; ++y) {
//                 for (int x = 0; x < a.cols; ++x) {
//                     for (int c = 0; c < a.channels(); ++c) {
//                         uchar aVal = a.at<cv::Vec3b>(y, x)[c];
//                         uchar bVal = b.at<cv::Vec3b>(y, x)[c];
//                         uchar result = (aVal < 128)
//                             ? (2 * aVal * bVal / 255)
//                             : (255 - 2 * (255 - aVal) * (255 - bVal) / 255);
//                         blended_.at<cv::Vec3b>(y, x)[c] = result;
//                     }
//                 }
//             }
//             break;
//         case 4: // Difference
//             cv::absdiff(a, b, blended_);
//             break;
//     }
// }


// void BlendNode::Render() {
//     ImNodes::BeginNode(id_);

//     ImNodes::BeginNodeTitleBar();
//     ImGui::Text("Blend Node");
//     ImNodes::EndNodeTitleBar();

//     ImNodes::BeginInputAttribute(id_ * 10 + 1);
//     ImGui::Text("Image A");
//     ImNodes::EndInputAttribute();

//     ImNodes::BeginInputAttribute(id_ * 10 + 2);
//     ImGui::Text("Image B");
//     ImNodes::EndInputAttribute();

//     ImNodes::BeginOutputAttribute(id_ * 10 + 3);
//     ImGui::Text("Blended Output");
//     ImNodes::EndOutputAttribute();

//     const char* modes[] = { "Normal", "Multiply", "Screen", "Overlay", "Difference" };
//     ImGui::Combo("Blend Mode", &blendMode_, modes, IM_ARRAYSIZE(modes));
//     ImGui::SliderFloat("Opacity", &opacity_, 0.0f, 1.0f);

//     ImNodes::EndNode();
// }

// #include "BlendNode.h"
// #include <imgui.h>
// #include <imnodes.h>
// #include <algorithm>

// BlendNode::BlendNode(int id)
//     : id_(id)
// {
//     inputAttrA_ = id_ * 10 + 1;
//     inputAttrB_ = id_ * 10 + 2;
//     outputAttr_ = id_ * 10 + 3;
// }

// void BlendNode::SetInputImages(const cv::Mat& imgA, const cv::Mat& imgB) {
//     imageA_ = imgA.clone();
//     imageB_ = imgB.clone();
//     ApplyBlend();
// }

// void BlendNode::ApplyBlend() {
//     if (imageA_.empty() || imageB_.empty()) {
//         outputImage_.release();
//         return;
//     }
//     // resize B to A if needed
//     if (imageB_.size() != imageA_.size())
//         cv::resize(imageB_, imageB_, imageA_.size());

//     cv::Mat fa, fb;
//     imageA_.convertTo(fa, CV_32F, 1.0f/255.0f);
//     imageB_.convertTo(fb, CV_32F, 1.0f/255.0f);
//     cv::Mat fc = fa.clone();

//     switch (mode_) {
//         case 0: // Normal: just mix
//             fc = fb;
//             break;
//         case 1: // Multiply
//             fc = fa.mul(fb);
//             break;
//         case 2: // Screen: 1 - (1-A)*(1-B)
//             fc = 1.0f - (1.0f - fa).mul(1.0f - fb);
//             break;
//         case 3: // Overlay
//             fc = cv::Mat(fa.size(), fa.type());
//             for (int y = 0; y < fa.rows; y++) {
//                 for (int x = 0; x < fa.cols; x++) {
//                     for (int c = 0; c < fa.channels(); c++) {
//                         float a = fa.at<cv::Vec3f>(y,x)[c];
//                         float b = fb.at<cv::Vec3f>(y,x)[c];
//                         float o = (a < 0.5f)
//                                   ? (2.0f * a * b)
//                                   : (1.0f - 2.0f * (1.0f - a) * (1.0f - b));
//                         fc.at<cv::Vec3f>(y,x)[c] = o;
//                     }
//                 }
//             }
//             break;
//         case 4: // Difference: |A - B|
//             fc = cv::abs(fa - fb);
//             break;
//     }

//     // mix with original A
//     outputImage_ = cv::Mat(fa.size(), fa.type());
//     cv::Mat mix = fa * (1.0f - opacity_) + fc * opacity_;
//     mix.convertTo(outputImage_, CV_8U, 255.0f);
// }

// void BlendNode::Render() {
//     ImNodes::BeginNode(id_);

//     ImNodes::BeginNodeTitleBar();
//     ImGui::Text("Blend Node");
//     ImNodes::EndNodeTitleBar();

//     // Input A
//     ImNodes::BeginInputAttribute(inputAttrA_);
//     ImGui::Text("A");
//     ImNodes::EndInputAttribute();

//     // Input B
//     ImNodes::BeginInputAttribute(inputAttrB_);
//     ImGui::Text("B");
//     ImNodes::EndInputAttribute();

//     // Mode selector
//     const char* modes[] = { "Normal", "Multiply", "Screen", "Overlay", "Difference" };
//     if (ImGui::Combo("Mode", &mode_, modes, IM_ARRAYSIZE(modes))) {
//         ApplyBlend();
//     }

//     // Opacity slider
//     if (ImGui::SliderFloat("Opacity", &opacity_, 0.0f, 1.0f)) {
//         ApplyBlend();
//     }

//     // Output
//     ImNodes::BeginOutputAttribute(outputAttr_);
//     ImGui::Text("Out");
//     ImNodes::EndOutputAttribute();

//     ImNodes::EndNode();
// }

// BlendNode.cpp
#include "BlendNode.h"
#include <imgui.h>
#include <imnodes.h>
#include <opencv2/imgproc.hpp>  // For cv::cvtColor
#include <opencv2/imgcodecs.hpp> // Add this for cv::imread
#include <GL/gl.h>
#include <cstdio>
#include <tinyfiledialogs.h> // For file dialog

BlendNode::BlendNode(int id)
    : id_(id), blendMode_(0), opacity_(1.0f), imageAvailable_(false), textureID_(0) {
    printf("Debug: BlendNode(%d) constructed\n", id_);
}

int BlendNode::GetId() const {
    return id_;
}

void BlendNode::SetInputImageA(const cv::Mat& img) {
    imageA_ = img.clone();
    BlendImages();
}

void BlendNode::SetInputImageB(const cv::Mat& img) {
    imageB_ = img.clone();
    BlendImages();
}

void BlendNode::LoadImageB(const std::string& path) {
    cv::Mat img = cv::imread(path, cv::IMREAD_COLOR); // Now recognized
    printf("Debug: imread result empty = %d\n", img.empty());
    if (!img.empty()) {
        imageB_ = img;
        printf("Debug: BlendNode(%d) loaded imageB from %s, size %dx%d\n", id_, path.c_str(), img.cols, img.rows);
        BlendImages();
    } else {
        printf("Debug: BlendNode(%d) failed to load image from %s\n", id_, path.c_str());
    }
}

void BlendNode::BlendImages() {
    if (imageA_.empty() || imageB_.empty()) {
        imageAvailable_ = false;
        blended_.release();
        return;
    }

    if (imageA_.size() != imageB_.size()) {
        cv::resize(imageB_, imageB_, imageA_.size());
    }

    cv::Mat result;
    switch (blendMode_) {
        case 0: // Add
            cv::addWeighted(imageA_, opacity_, imageB_, 1.0 - opacity_, 0.0, result);
            break;
        case 1: // Multiply
            cv::multiply(imageA_, imageB_, result, opacity_ / 255.0);
            break;
        case 2: // Average
            cv::addWeighted(imageA_, opacity_, imageB_, 1.0 - opacity_, 0.0, result);
            break;
        default:
            result = imageA_.clone();
            break;
    }

    blended_ = result;
    imageAvailable_ = true;
    UploadTexture();
}

cv::Mat BlendNode::GetBlendedImage() const {
    return blended_;
}

void BlendNode::UploadTexture() {
    if (!imageAvailable_) return;

    cv::Mat uploadImage;
    GLenum format;

    if (blended_.channels() == 3) {
        cv::cvtColor(blended_, uploadImage, cv::COLOR_BGR2RGB);
        format = GL_RGB;
    } else if (blended_.channels() == 4) {
        cv::cvtColor(blended_, uploadImage, cv::COLOR_BGRA2RGBA);
        format = GL_RGBA;
    } else if (blended_.channels() == 1) {
        cv::cvtColor(blended_, uploadImage, cv::COLOR_GRAY2RGB);
        format = GL_RGB;
    } else {
        printf("BlendNode(%d): Unsupported channel count %d\n", id_, blended_.channels());
        return;
    }

    if (textureID_) {
        glDeleteTextures(1, &textureID_);
    }

    glGenTextures(1, &textureID_);
    glBindTexture(GL_TEXTURE_2D, textureID_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, format, uploadImage.cols, uploadImage.rows, 0, format, GL_UNSIGNED_BYTE, uploadImage.data);

    printf("BlendNode(%d): Texture uploaded (%dx%d)\n", id_, uploadImage.cols, uploadImage.rows);
}

void BlendNode::Render() {
    ImNodes::BeginNode(id_);

    ImNodes::BeginNodeTitleBar();
    ImGui::Text("Blend Node");
    ImNodes::EndNodeTitleBar();

    ImNodes::BeginInputAttribute(id_ * 10 + 1);
    ImGui::Text("Image A");
    ImNodes::EndInputAttribute();

    ImNodes::BeginInputAttribute(id_ * 10 + 2);
    ImGui::Text("Image B");
    if (ImGui::Button("Browse B")) {
        const char* filters[] = { "*.png", "*.jpg", "*.jpeg" };
        const char* path = tinyfd_openFileDialog("Select Image B", "", 3, filters, NULL, 0);
        if (path) {
            LoadImageB(path);
        }
    }
    ImNodes::EndInputAttribute();

    ImNodes::BeginOutputAttribute(id_ * 10 + 3);
    ImGui::Text("Blended Out");
    ImNodes::EndOutputAttribute();

    const char* modes[] = { "Add", "Multiply", "Average" };
    ImGui::Combo("Blend Mode", &blendMode_, modes, IM_ARRAYSIZE(modes));
    ImGui::SliderFloat("Opacity", &opacity_, 0.0f, 1.0f);

    if (imageAvailable_) {
        ImGui::Text("Preview:");
        ImGui::Image((ImTextureID)(intptr_t)textureID_, ImVec2(128, 128));
    } else {
        ImGui::TextDisabled("Waiting for two inputs...");
    }

    ImNodes::EndNode();
}

bool BlendNode::HasBothInputs() const {
    return !imageA_.empty() && !imageB_.empty();
}