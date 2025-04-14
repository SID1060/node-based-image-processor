#include "BrightnessContrastNode.h"
#include <imgui.h>
#include <imnodes.h>
#include <opencv2/imgproc.hpp>
#include <cstdio>

BrightnessContrastNode::BrightnessContrastNode(int id)
    : id_(id)
{
    printf("Debug: BrightnessContrastNode(%d) constructed\n", id_);
}

void BrightnessContrastNode::SetInputImage(const cv::Mat& img) {
    inputImage_ = img.clone();
    if (inputImage_.empty()) {
        printf("Debug: BrightnessContrastNode(%d) got empty input\n", id_);
        return;
    }
    // Apply brightness & contrast
    inputImage_.convertTo(outputImage_, -1, contrast_, brightness_);
    printf("Debug: BrightnessContrastNode(%d) processed image %dx%d\n",
           id_, outputImage_.cols, outputImage_.rows);
}

void BrightnessContrastNode::Render() {
    ImNodes::BeginNode(id_);
    ImNodes::BeginNodeTitleBar();
    ImGui::Text("Brightness/Contrast");
    ImNodes::EndNodeTitleBar();

    // Input port
    ImNodes::BeginInputAttribute(id_ * 10 + 1);
    ImGui::Text("In");
    ImNodes::EndInputAttribute();

    // Output port
    ImNodes::BeginOutputAttribute(id_ * 10 + 2);
    ImGui::Text("Out");
    ImNodes::EndOutputAttribute();

    if (ImGui::SliderInt("Brightness", &brightness_, -100, 100)) {
        if (!inputImage_.empty()) SetInputImage(inputImage_);
    }
    if (ImGui::SliderFloat("Contrast", &contrast_, 0.0f, 3.0f)) {
        if (!inputImage_.empty()) SetInputImage(inputImage_);
    }
    if (ImGui::Button("Reset B")) {
        brightness_ = 0;
        if (!inputImage_.empty()) SetInputImage(inputImage_);
    }
    ImGui::SameLine();
    if (ImGui::Button("Reset C")) {
        contrast_ = 1.0f;
        if (!inputImage_.empty()) SetInputImage(inputImage_);
    }

    ImNodes::EndNode();
}
