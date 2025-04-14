#include "NoiseNode.h"
#include <imgui.h>
#include <imnodes.h>
#include <cmath>
#include <cstdlib>

NoiseNode::NoiseNode(int id)
    : id_(id)
{
    outputAttr_ = id_ * 10 + 1;
    GenerateNoise();
}

void NoiseNode::Render() {
    ImNodes::BeginNode(id_);

    ImNodes::BeginNodeTitleBar();
    ImGui::Text("Noise Generator");
    ImNodes::EndNodeTitleBar();

    // Controls
    ImGui::Combo("Type", &noiseType_, "Perlin\0Simplex\0Worley\0");
    ImGui::SliderInt("Width", &width_, 64, 1024);
    ImGui::SliderInt("Height", &height_, 64, 1024);
    ImGui::SliderFloat("Scale", &scale_, 1.0f, 100.0f);
    ImGui::SliderInt("Octaves", &octaves_, 1, 8);
    ImGui::SliderFloat("Persistence", &persistence_, 0.1f, 1.0f);

    if (ImGui::Button("Generate")) {
        GenerateNoise();
    }

    ImNodes::BeginOutputAttribute(outputAttr_);
    ImGui::Text("Out");
    ImNodes::EndOutputAttribute();

    ImNodes::EndNode();
}

cv::Mat NoiseNode::GetOutputImage() const {
    if (noiseImage_.empty()) {
        GenerateNoise();
    }
    return noiseImage_;
}

void NoiseNode::GenerateNoise() const {
    switch (noiseType_) {
        case 0: noiseImage_ = GeneratePerlin(); break;
        case 1: noiseImage_ = GenerateSimplex(); break;
        case 2: noiseImage_ = GenerateWorley(); break;
    }
}

// Simple Perlin-like noise (placeholder)
cv::Mat NoiseNode::GeneratePerlin() const {
    cv::Mat img(height_, width_, CV_8UC1);
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            float nx = x / scale_, ny = y / scale_;
            float val = 0, amp = 1, freq = 1, maxAmp = 0;
            for (int o = 0; o < octaves_; ++o) {
                val   += std::sin(nx*freq)*std::cos(ny*freq) * amp;
                maxAmp += amp;
                amp    *= persistence_;
                freq   *= 2;
            }
            val = (val/maxAmp + 1)*0.5f;
            img.at<uchar>(y,x) = static_cast<uchar>(val * 255);
        }
    }
    return img;
}

// Simplex-like placeholder
cv::Mat NoiseNode::GenerateSimplex() const {
    cv::Mat img(height_, width_, CV_8UC1);
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            float v = std::fmod(std::sin(x/scale_*2.3f + y/scale_*1.7f), 1.0f);
            img.at<uchar>(y,x) = static_cast<uchar>((v+1)*0.5f * 255);
        }
    }
    return img;
}

// Worley-like placeholder
cv::Mat NoiseNode::GenerateWorley() const {
    cv::Mat img(height_, width_, CV_8UC1, cv::Scalar(0));
    std::vector<cv::Point> pts;
    int count = 30;
    for (int i = 0; i < count; ++i)
        pts.emplace_back(rand()%width_, rand()%height_);

    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            float md = 1e6f;
            for (auto &p: pts)
                md = std::min(md, std::hypotf(x-p.x, y-p.y));
            img.at<uchar>(y,x) = static_cast<uchar>(std::clamp(md*2, 0.0f, 255.0f));
        }
    }
    return img;
}
