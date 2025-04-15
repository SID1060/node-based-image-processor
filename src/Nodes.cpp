#include "Nodes.h"
#include <imgui.h>
#include <imnodes.h>
#include <imnodes_internal.h>
#include <opencv2/imgcodecs.hpp>
#include <stdio.h>
#include "ImGuiFileDialog.h" // Include ImGuiFileDialog

ImageInputNode::ImageInputNode(int id) : id_(id) {}

void ImageInputNode::LoadImage(const std::string& path) {
    image_ = cv::imread(path, cv::IMREAD_COLOR); // Load as color image by default
    printf("Debug: imread result empty = %d\n", image_.empty());
    if (!image_.empty()) {
        imagePath_ = path;
        imageLoaded_ = true;
        printf("Loaded image: %s (%dx%d)\n", path.c_str(), image_.cols, image_.rows);
    } else {
        imageLoaded_ = false;
        printf("Failed to load image: %s (Check file format or path)\n", path.c_str());
    }
}

void ImageInputNode::Render() {
    printf("Debug: Entering ImageInputNode::Render, Scope: %d\n", GImNodes ? GImNodes->CurrentScope : -1);

    ImNodes::BeginNode(id_);
    printf("Debug: After BeginNode, Scope: %d\n", GImNodes ? GImNodes->CurrentScope : -1);

    ImNodes::BeginNodeTitleBar();
    ImGui::Text("Image Input");
    ImNodes::EndNodeTitleBar();

    ImNodes::BeginOutputAttribute(id_ * 10 + 1);
    ImGui::Text("Image");
    ImNodes::EndOutputAttribute();

    // File dialog button
    if (ImGui::Button(("Browse##" + std::to_string(id_)).c_str())) {
        IGFD::FileDialogConfig config;
        config.path = "."; // Start in current directory
        ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey" + std::to_string(id_), "Choose Image", ".png,.jpg,.jpeg,.bmp", config);
    }

    // Display file dialog if open
    if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey" + std::to_string(id_))) {
        if (ImGuiFileDialog::Instance()->IsOk()) {
            std::string filePath = ImGuiFileDialog::Instance()->GetFilePathName();
            LoadImage(filePath);
        }
        ImGuiFileDialog::Instance()->Close();
    }

    // Display image info if loaded
    if (imageLoaded_) {
        ImGui::Text("Loaded: %s", imagePath_.c_str());
        ImGui::Text("Size: %dx%d", image_.cols, image_.rows);
        // Optional: Add a small preview (requires texture upload, similar to OutputNode)
    } else {
        ImGui::TextDisabled("No image loaded.");
    }

    ImNodes::EndNode();
    printf("Debug: Leaving ImageInputNode::Render, Scope: %d\n", GImNodes ? GImNodes->CurrentScope : -1);
}