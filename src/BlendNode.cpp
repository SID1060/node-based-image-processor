#include "BlendNode.h"
#include <imgui.h>
#include <imnodes.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <GL/gl.h>
#include <cstdio>
#include <tinyfiledialogs.h>
#include <chrono>

BlendNode::BlendNode(int id)
    : id_(id), blendMode_(0), opacity_(0.5f), imageAvailable_(false), textureID_(0), needsUpdate_(true) {
    printf("Debug: BlendNode(%d) constructed\n", id_);
}

int BlendNode::GetId() const {
    return id_;
}

void BlendNode::SetInputImageA(const cv::Mat& img) {
    if (img.empty()) return;
    if (imageA_.empty() || imageA_.size() != img.size()) {
        imageA_ = img.clone();
        needsUpdate_ = true;
    } else {
        img.copyTo(imageA_); // Avoid cloning if size matches
    }
    printf("Debug: BlendNode(%d) set InputA (size %dx%d)\n", id_, img.cols, img.rows);
    if (HasBothInputs()) BlendImages();
}

void BlendNode::SetInputImageB(const cv::Mat& img) {
    if (img.empty()) return;
    if (imageB_.empty() || imageB_.size() != img.size()) {
        imageB_ = img.clone();
        needsUpdate_ = true;
    } else {
        img.copyTo(imageB_); // Avoid cloning if size matches
    }
    printf("Debug: BlendNode(%d) set InputB (size %dx%d)\n", id_, img.cols, img.rows);
    if (HasBothInputs()) BlendImages();
}

void BlendNode::LoadImageB(const std::string& path) {
    cv::Mat img = cv::imread(path, cv::IMREAD_COLOR);
    printf("Debug: imread result empty = %d for path: %s\n", img.empty(), path.c_str());
    if (!img.empty()) {
        if (imageB_.empty() || imageB_.size() != img.size()) {
            imageB_ = img.clone();
        } else {
            img.copyTo(imageB_);
        }
        needsUpdate_ = true;
        printf("Debug: BlendNode(%d) loaded imageB from %s, size %dx%d\n", id_, path.c_str(), img.cols, img.rows);
    } else {
        printf("Debug: BlendNode(%d) failed to load image from %s\n", id_, path.c_str());
        return;
    }
    if (HasBothInputs()) BlendImages();
}

void BlendNode::BlendImages() {
    if (!needsUpdate_ || !HasBothInputs()) {
        imageAvailable_ = HasBothInputs();
        return;
    }

    cv::Mat a = imageA_, b = imageB_;
    if (a.size() != b.size()) {
        cv::resize(b, b, a.size());
        printf("Debug: BlendNode(%d) resized imageB to %dx%d\n", id_, a.cols, a.rows);
    }

    auto start = std::chrono::high_resolution_clock::now();
    cv::Mat result;
    try {
        switch (blendMode_) {
            case 0: // Add
                cv::addWeighted(a, opacity_, b, 1.0 - opacity_, 0.0, result, a.depth());
                break;
            case 1: // Multiply
                cv::multiply(a, b, result, opacity_ / 255.0, a.depth());
                break;
            case 2: // Average
                cv::addWeighted(a, 0.5, b, 0.5, 0.0, result, a.depth());
                break;
            default:
                result = a.clone();
                break;
        }
    } catch (const cv::Exception& e) {
        printf("Debug: BlendNode(%d) OpenCV error: %s\n", id_, e.what());
        return;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    printf("Debug: BlendNode(%d) blending took %ld ms\n", id_, duration);

    if (result.empty()) {
        printf("Debug: BlendNode(%d) blended result is empty!\n", id_);
        return;
    }
    cv::resize(result, blended_, cv::Size(640, 640)); // Downscale to 640x640
    if (blended_.empty()) {
        printf("Debug: BlendNode(%d) downscaled blended is empty!\n", id_);
        return;
    }
    // Debug: Save blended image to verify
    cv::imwrite("debug_blended.png", blended_);

    imageAvailable_ = true;
    needsUpdate_ = false;
    UpdatePreview();
}

cv::Mat BlendNode::GetBlendedImage() const {
    return blended_.clone();
}

void BlendNode::UploadTexture() {
    if (!imageAvailable_ || preview_.empty()) {
        printf("Debug: BlendNode(%d) UploadTexture skipped: imageAvailable=%d, preview.empty=%d\n",
               id_, imageAvailable_, preview_.empty());
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

    cv::Mat uploadImage = preview_.clone();
    GLenum format;
    if (uploadImage.channels() == 3) {
        cv::cvtColor(uploadImage, uploadImage, cv::COLOR_BGR2RGB);
        format = GL_RGB;
    } else if (uploadImage.channels() == 4) {
        cv::cvtColor(uploadImage, uploadImage, cv::COLOR_BGRA2RGBA);
        format = GL_RGBA;
    } else if (uploadImage.channels() == 1) {
        cv::cvtColor(uploadImage, uploadImage, cv::COLOR_GRAY2RGB);
        format = GL_RGB;
    } else {
        printf("Debug: BlendNode(%d): Unsupported channel count %d\n", id_, uploadImage.channels());
        return;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, format, uploadImage.cols, uploadImage.rows, 0, format, GL_UNSIGNED_BYTE, uploadImage.data);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("Debug: BlendNode(%d): OpenGL error %d after texture upload\n", id_, error);
    } else {
        printf("Debug: BlendNode(%d): Texture uploaded (%dx%d)\n", id_, uploadImage.cols, uploadImage.rows);
    }
    // Debug: Save preview to verify
    cv::imwrite("debug_preview.png", preview_);
}

void BlendNode::UpdatePreview() {
    if (!blended_.empty()) {
        cv::resize(blended_, preview_, cv::Size(256, 256)); // Downscale to 256x256 for preview
        if (preview_.empty()) {
            printf("Debug: BlendNode(%d) preview is empty after resize!\n", id_);
        }
        UploadTexture();
    } else {
        printf("Debug: BlendNode(%d) UpdatePreview skipped: blended_ is empty\n", id_);
    }
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
            LoadImageB(path); // Process the selected file
        } else {
            printf("Debug: BlendNode(%d): No file selected\n", id_);
        }
    }
    ImNodes::EndInputAttribute();

    ImNodes::BeginOutputAttribute(id_ * 10 + 3);
    ImGui::Text("Blended Out");
    ImNodes::EndOutputAttribute();

    const char* modes[] = { "Add", "Multiply", "Average" };
    if (ImGui::Combo("Blend Mode", &blendMode_, modes, IM_ARRAYSIZE(modes)) ||
        ImGui::SliderFloat("Opacity", &opacity_, 0.0f, 1.0f)) {
        needsUpdate_ = true;
        if (HasBothInputs()) BlendImages();
    }

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