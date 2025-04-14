#include "ConvolutionNode.h"
#include <imgui.h>
#include <imnodes.h>
#include <cstring>

ConvolutionNode::ConvolutionNode(int id)
    : id_(id), kernelSize_(3), kernelChanged_(true) {
    std::fill(kernel_.begin(), kernel_.end(), 0);
    kernel_[kernelSize_ * kernelSize_ / 2] = 1; // identity kernel
}

void ConvolutionNode::SetInputImage(const cv::Mat& img) {
    inputImage_ = img.clone();
    kernelChanged_ = true;
    ApplyKernel();
}

const cv::Mat& ConvolutionNode::GetOutputImage() const {
    return outputImage_;
}

void ConvolutionNode::ApplyKernel() {
    if (inputImage_.empty()) return;

    cv::Mat kernelMat(kernelSize_, kernelSize_, CV_32F);
    for (int y = 0; y < kernelSize_; ++y)
        for (int x = 0; x < kernelSize_; ++x)
            kernelMat.at<float>(y, x) = kernel_[y * kernelSize_ + x];

    cv::filter2D(inputImage_, outputImage_, -1, kernelMat);
    kernelChanged_ = false;
}

void ConvolutionNode::SetPreset(const std::string& name) {
    std::fill(kernel_.begin(), kernel_.end(), 0);
    kernelSize_ = 3;

    if (name == "Sharpen") {
        kernel_ = { 0, -1,  0,
                   -1,  5, -1,
                    0, -1,  0 };
    } else if (name == "Emboss") {
        kernel_ = { -2, -1, 0,
                    -1,  1, 1,
                     0,  1, 2 };
    } else if (name == "Edge Enhance") {
        kernel_ = { 0,  0,  0,
                   -1,  1,  0,
                    0,  0,  0 };
    }

    kernelChanged_ = true;
    ApplyKernel();
}

void ConvolutionNode::Render() {
    ImNodes::BeginNode(id_);

    ImNodes::BeginNodeTitleBar();
    ImGui::Text("Convolution Node");
    ImNodes::EndNodeTitleBar();

    ImNodes::BeginInputAttribute(id_ * 10 + 1);
    ImGui::Text("Image In");
    ImNodes::EndInputAttribute();

    ImGui::Separator();

    ImGui::Text("Kernel Size:");
    ImGui::RadioButton("3x3", &kernelSize_, 3); ImGui::SameLine();
    ImGui::RadioButton("5x5", &kernelSize_, 5);

    if (ImGui::Button("Sharpen")) SetPreset("Sharpen");
    ImGui::SameLine();
    if (ImGui::Button("Emboss")) SetPreset("Emboss");
    ImGui::SameLine();
    if (ImGui::Button("Edge Enhance")) SetPreset("Edge Enhance");

    ImGui::Text("Kernel Values:");
    for (int y = 0; y < kernelSize_; ++y) {
        for (int x = 0; x < kernelSize_; ++x) {
            ImGui::PushID(y * kernelSize_ + x);
            ImGui::SetNextItemWidth(40);
            if (ImGui::InputFloat("##k", &kernel_[y * kernelSize_ + x], 0.1f, 1.0f, "%.1f"))
                kernelChanged_ = true;
            ImGui::PopID();
            ImGui::SameLine();
        }
        ImGui::NewLine();
    }

    if (kernelChanged_) ApplyKernel();

    ImNodes::BeginOutputAttribute(id_ * 10 + 2);
    ImGui::Text("Image Out");
    ImNodes::EndOutputAttribute();

    ImNodes::EndNode();
}
