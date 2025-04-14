#include "BlurNode.h"
#include <imgui.h>
#include <imnodes.h>
#include <opencv2/imgproc.hpp>
#include <cstdio>

BlurNode::BlurNode(int id)
    : id_(id), radius_(5), directional_(false)
{
    printf("Debug: BlurNode(%d) constructed\n", id_);
}

int BlurNode::GetId() const {
    return id_;
}

void BlurNode::SetInputImage(const cv::Mat& img) {
    inputImage_ = img.clone();
    ApplyBlur();
}

const cv::Mat& BlurNode::GetOutputImage() const {
    return outputImage_;
}

void BlurNode::ApplyBlur() {
    if (inputImage_.empty()) return;

    int ksize = std::max(1, radius_ * 2 + 1);
    if (directional_) {
        cv::GaussianBlur(inputImage_, outputImage_, cv::Size(ksize, 1), 0);
    } else {
        cv::GaussianBlur(inputImage_, outputImage_, cv::Size(ksize, ksize), 0);
    }

    printf("Debug: BlurNode(%d) applied blur, radius = %d, directional = %d\n", id_, radius_, directional_);
}

void BlurNode::ShowKernelPreview() {
    ImGui::Text("Kernel Preview:");
    int size = radius_ * 2 + 1;
    std::vector<float> values(size);

    float sigma = 0.3f * ((size - 1) * 0.5f - 1) + 0.8f;
    float sum = 0.0f;
    for (int i = 0; i < size; ++i) {
        int x = i - radius_;
        values[i] = std::exp(-(x * x) / (2 * sigma * sigma));
        sum += values[i];
    }

    for (auto& v : values) v /= sum;

    for (int i = 0; i < size; ++i) {
        ImGui::Text("[%2d] %.4f", i - radius_, values[i]);
    }
}

void BlurNode::Render() {
    ImNodes::BeginNode(id_);

    ImNodes::BeginNodeTitleBar();
    ImGui::Text("Blur Node");
    ImNodes::EndNodeTitleBar();

    ImNodes::BeginInputAttribute(id_ * 10 + 1);
    ImGui::Text("In");
    ImNodes::EndInputAttribute();

    ImNodes::BeginOutputAttribute(id_ * 10 + 2);
    ImGui::Text("Out");
    ImNodes::EndOutputAttribute();

    bool changed = false;
    changed |= ImGui::SliderInt("Radius", &radius_, 1, 20);
    changed |= ImGui::Checkbox("Directional (Horizontal)", &directional_);

    if (changed && !inputImage_.empty()) {
        ApplyBlur();
    }

    ShowKernelPreview();

    ImNodes::EndNode();
}
