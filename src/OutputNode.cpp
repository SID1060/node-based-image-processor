#include "OutputNode.h"
#include <imgui.h>
#include <imnodes.h>
#include <opencv2/imgcodecs.hpp>
#include <tinyfiledialogs.h>

OutputNode::OutputNode(int id) : id_(id) {}

void OutputNode::SetInputImage(const cv::Mat& img) {
    image_ = img.clone();
    imageAvailable_ = !img.empty();
}

void OutputNode::SaveImage() {
    if (!imageAvailable_) return;
    const char* filters[] = { "*.png", "*.jpg", "*.jpeg" };
    const char* path = tinyfd_saveFileDialog("Save Image", "output.png", 2, filters, nullptr);
    if (path) {
        std::vector<int> params = { cv::IMWRITE_JPEG_QUALITY, quality_ };
        cv::imwrite(path, image_, params);
    }
}

void OutputNode::Render() {
    ImNodes::BeginNode(id_);

    ImNodes::BeginNodeTitleBar();
    ImGui::Text("Output Node");
    ImNodes::EndNodeTitleBar();

    ImNodes::BeginInputAttribute(id_ * 10 + 1);
    ImGui::Text("Image Input");
    ImNodes::EndInputAttribute();

    if (imageAvailable_) {
        ImGui::Text("Preview:");
        ImGui::Text("Size: %dx%d", image_.cols, image_.rows);
        ImGui::SliderInt("Quality", &quality_, 1, 100);
        if (ImGui::Button("Save Image")) {
            SaveImage();
        }
    } else {
        ImGui::Text("No image connected.");
    }

    ImNodes::EndNode();
}
