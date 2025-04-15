#include "OutputNode.h"
#include <imgui.h>
#include <imnodes.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <tinyfiledialogs.h>
#include <SDL_opengl.h>
#include <cstdio>
#include <algorithm>
#include <cctype>
#include <vector>
#include <string>

OutputNode::OutputNode(int id)
    : id_(id), textureID_(0), quality_(95), imageAvailable_(false), dirty_(false)
{
    printf("Debug: OutputNode(%d) constructed\n", id_);
}

int OutputNode::GetId() const {
    return id_;
}

void OutputNode::SetInputImage(const cv::Mat &img) {
    printf("Debug: OutputNode(%d)::SetInputImage called. img size = %dx%d\n", id_, img.cols, img.rows);
    image_ = img.clone();
    imageAvailable_ = !img.empty();
    dirty_ = true; // Mark dirty when new image arrives
}

// Allows external control to mark the image as needing update
void OutputNode::MarkDirty() {
    dirty_ = true;
}

void OutputNode::UploadTexture() {
    printf("Debug: OutputNode(%d)::UploadTexture()\n", id_);

    cv::Mat uploadImage;
    GLenum format;

    if (image_.channels() == 3) {
        cv::cvtColor(image_, uploadImage, cv::COLOR_BGR2RGB);
        format = GL_RGB;
    } else if (image_.channels() == 4) {
        cv::cvtColor(image_, uploadImage, cv::COLOR_BGRA2RGBA);
        format = GL_RGBA;
    } else if (image_.channels() == 1) {
        cv::cvtColor(image_, uploadImage, cv::COLOR_GRAY2RGB);
        format = GL_RGB;
    } else {
        printf("Error: Unsupported number of channels: %d\n", image_.channels());
        imageAvailable_ = false;
        return;
    }

    if (textureID_) {
        glDeleteTextures(1, &textureID_);
        textureID_ = 0;
    }

    glGenTextures(1, &textureID_);
    glBindTexture(GL_TEXTURE_2D, textureID_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(GL_TEXTURE_2D, 0, format,
                 uploadImage.cols, uploadImage.rows,
                 0, format, GL_UNSIGNED_BYTE,
                 uploadImage.data);

    printf("Debug: Texture %d uploaded (size: %dx%d, format: %s)\n",
           textureID_, uploadImage.cols, uploadImage.rows,
           format == GL_RGB ? "RGB" : "RGBA");
}

void OutputNode::SaveImage() {
    if (!imageAvailable_) return;

    const char* filters[] = { "*.png", "*.jpg", "*.jpeg" };
    const char* savePath = tinyfd_saveFileDialog("Save Image", "output.png", 3, filters, nullptr);
    if (!savePath) return;

    std::string pathStr(savePath);
    auto dotPos = pathStr.find_last_of('.');
    std::string ext;
    if (dotPos != std::string::npos) {
        ext = pathStr.substr(dotPos + 1);
        std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    }

    std::vector<int> params;
    if (ext == "jpg" || ext == "jpeg") {
        params = { cv::IMWRITE_JPEG_QUALITY, quality_ };
    }

    bool ok = cv::imwrite(pathStr, image_, params);
    if (!ok) {
        printf("Error: Failed to save image to %s\n", pathStr.c_str());
    } else {
        printf("Saved image to %s\n", pathStr.c_str());
    }
}

void OutputNode::Render() {
    printf("Debug: OutputNode(%d)::Render(), imageAvailable = %d, dirty = %d\n", id_, imageAvailable_, dirty_);
    ImNodes::BeginNode(id_);

    ImNodes::BeginNodeTitleBar();
    ImGui::Text("Output Node");
    ImNodes::EndNodeTitleBar();

    ImNodes::BeginInputAttribute(id_ * 10 + 1);
    ImGui::Text("Image In");
    ImNodes::EndInputAttribute();

    if (imageAvailable_) {
        if (dirty_) {
            UploadTexture();
            dirty_ = false;
        }

        ImGui::Text("Preview:");
        ImGui::Image((ImTextureID)(intptr_t)textureID_, ImVec2(128,128));
        ImGui::SliderInt("Quality", &quality_, 1, 100);
        if (ImGui::Button("Save Image")) {
            SaveImage();
        }
    } else {
        ImGui::TextDisabled("No image connected.");
    }

    ImNodes::EndNode();
}

