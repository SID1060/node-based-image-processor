// #include "OutputNode.h"
// #include <imgui.h>
// #include <imnodes.h>
// #include <opencv2/imgcodecs.hpp>
// #include <tinyfiledialogs.h>

// OutputNode::OutputNode(int id) : id_(id) {}

// void OutputNode::SetInputImage(const cv::Mat& img) {
//     image_ = img.clone();
//     imageAvailable_ = !img.empty();
// }

// void OutputNode::SaveImage() {
//     if (!imageAvailable_) return;
//     const char* filters[] = { "*.png", "*.jpg", "*.jpeg" };
//     const char* path = tinyfd_saveFileDialog("Save Image", "output.png", 2, filters, nullptr);
//     if (path) {
//         std::vector<int> params = { cv::IMWRITE_JPEG_QUALITY, quality_ };
//         cv::imwrite(path, image_, params);
//     }
// }

// void OutputNode::Render() {
//     ImNodes::BeginNode(id_);

//     ImNodes::BeginNodeTitleBar();
//     ImGui::Text("Output Node");
//     ImNodes::EndNodeTitleBar();

//     ImNodes::BeginInputAttribute(id_ * 10 + 1);
//     ImGui::Text("Image Input");
//     ImNodes::EndInputAttribute();

//     if (imageAvailable_) {
//         ImGui::Text("Preview:");
//         ImGui::Text("Size: %dx%d", image_.cols, image_.rows);
//         ImGui::SliderInt("Quality", &quality_, 1, 100);
//         if (ImGui::Button("Save Image")) {
//             SaveImage();
//         }
//     } else {
//         ImGui::Text("No image connected.");
//     }

//     ImNodes::EndNode();
// }


// #include "OutputNode.h"
// #include <imgui.h>
// #include <imnodes.h>
// #include <opencv2/imgcodecs.hpp>
// #include <tinyfiledialogs.h>
// #include <SDL_opengl.h>
// #include <string>
// #include <vector>

// void OutputNode::SaveImage() {
//     if (!imageAvailable_) return;

//     // Ask user where to save
//     const char* filters[] = { "*.png", "*.jpg", "*.jpeg" };
//     const char* savePath = tinyfd_saveFileDialog(
//         "Save Image",
//         "output.png",
//         3,
//         filters,
//         nullptr
//     );
//     if (!savePath) {
//         // user cancelled
//         return;
//     }

//     // Determine extension
//     std::string pathStr(savePath);
//     auto dotPos = pathStr.find_last_of('.');
//     std::string ext;
//     if (dotPos != std::string::npos) {
//         ext = pathStr.substr(dotPos + 1);
//         // to lowercase
//         for (auto& c : ext) c = static_cast<char>(tolower(c));
//     }

//     // Set encoding params if JPEG
//     std::vector<int> params;
//     if (ext == "jpg" || ext == "jpeg") {
//         params = { cv::IMWRITE_JPEG_QUALITY, quality_ };
//     }

//     // Write file
//     bool ok = cv::imwrite(pathStr, image_, params);
//     if (!ok) {
//         printf("Error: Failed to save image to %s\n", pathStr.c_str());
//     } else {
//         printf("Saved image to %s\n", pathStr.c_str());
//     }
// }

// #include "OutputNode.h"
// #include <imgui.h>
// #include <imnodes.h>
// #include <opencv2/imgcodecs.hpp>
// #include <tinyfiledialogs.h>
// #include <SDL_opengl.h>
// #include <vector>
// #include <string>
// #include <cstdio>
// #include <algorithm>
// #include <cctype>

// // Constructor
// OutputNode::OutputNode(int id)
//     : id_(id), textureID_(0), quality_(95), imageAvailable_(false)
// {}

// // Returns the node's ID.
// int OutputNode::GetId() const {
//     return id_;
// }

// // Sets the input image. If valid, uploads it to an OpenGL texture.
// void OutputNode::SetInputImage(const cv::Mat &img) {
//     image_ = img.clone();
//     imageAvailable_ = !image_.empty();
//     if (textureID_) {
//         glDeleteTextures(1, &textureID_);
//         textureID_ = 0;
//     }
//     if (imageAvailable_) {
//         UploadTexture();
//     }
// }

// // // Uploads the image data to an OpenGL texture.
// // void OutputNode::UploadTexture() {
// //     glGenTextures(1, &textureID_);
// //     glBindTexture(GL_TEXTURE_2D, textureID_);
// //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
// //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// //     glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
// //     GLenum format = (image_.channels() == 3) ? GL_RGB : GL_RGBA;
// //     glTexImage2D(GL_TEXTURE_2D, 0, format, image_.cols, image_.rows, 0, format, GL_UNSIGNED_BYTE, image_.data);
// // }

// void OutputNode::UploadTexture() {
//     cv::Mat uploadImage;
//     if (image_.channels() == 3) {
//         // Convert from BGR (default in OpenCV) to RGB
//         cv::cvtColor(image_, uploadImage, cv::COLOR_BGR2RGB);
//     } else {
//         uploadImage = image_;
//     }

//     glGenTextures(1, &textureID_);
//     glBindTexture(GL_TEXTURE_2D, textureID_);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//     glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

//     // Use the proper format; now it will be GL_RGB for 3-channel images
//     GLenum format = (uploadImage.channels() == 3) ? GL_RGB : GL_RGBA;
//     glTexImage2D(GL_TEXTURE_2D, 0, format, uploadImage.cols, uploadImage.rows,
//                  0, format, GL_UNSIGNED_BYTE, uploadImage.data);
// }


// // Opens a file dialog and saves the current image to disk.
// void OutputNode::SaveImage() {
//     if (!imageAvailable_) return;
//     const char* filters[] = { "*.png", "*.jpg", "*.jpeg" };
//     const char* savePath = tinyfd_saveFileDialog("Save Image", "output.png", 3, filters, nullptr);
//     if (!savePath) return;
//     std::string pathStr(savePath);
//     auto dotPos = pathStr.find_last_of('.');
//     std::string ext;
//     if (dotPos != std::string::npos) {
//         ext = pathStr.substr(dotPos + 1);
//         std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
//     }
//     std::vector<int> params;
//     if (ext == "jpg" || ext == "jpeg") {
//         params = { cv::IMWRITE_JPEG_QUALITY, quality_ };
//     }
//     bool ok = cv::imwrite(pathStr, image_, params);
//     if (!ok) {
//         printf("Error: Failed to save image to %s\n", pathStr.c_str());
//     } else {
//         printf("Saved image to %s\n", pathStr.c_str());
//     }
// }

// // Renders the Output node.
// void OutputNode::Render() {
//     ImNodes::BeginNode(id_);
    
//     ImNodes::BeginNodeTitleBar();
//     ImGui::Text("Output Node");
//     ImNodes::EndNodeTitleBar();
    
//     // Declare an input port.
//     ImNodes::BeginInputAttribute(id_ * 10 + 1);
//     ImGui::Text("Image In");
//     ImNodes::EndInputAttribute();
    
//     if (imageAvailable_) {
//         ImGui::Text("Preview:");
//         ImGui::Image((ImTextureID)(intptr_t)textureID_, ImVec2(128, 128));
//         ImGui::SliderInt("Quality", &quality_, 1, 100);
//         if (ImGui::Button("Save Image")) {
//             SaveImage();
//         }
//     } else {
//         ImGui::TextDisabled("No image connected.");
//     }
    
//     ImNodes::EndNode();
// }

// #include "OutputNode.h"
// #include <imgui.h>
// #include <imnodes.h>
// #include <opencv2/imgcodecs.hpp>
// #include <tinyfiledialogs.h>
// #include <SDL_opengl.h>
// #include <cstdio>
// #include <algorithm>
// #include <cctype>
// #include <vector>
// #include <string>

// // Constructor
// OutputNode::OutputNode(int id)
//     : id_(id), textureID_(0), quality_(95), imageAvailable_(false)
// {
//     printf("Debug: OutputNode(%d) constructed\n", id_);
// }

// // Accessor for node ID
// int OutputNode::GetId() const {
//     return id_;
// }

// // Sets the input image and uploads it as a texture.
// void OutputNode::SetInputImage(const cv::Mat &img) {
//     printf("Debug: OutputNode(%d)::SetInputImage called. img size = %dx%d\n", id_, img.cols, img.rows);
//     image_ = img.clone();
//     imageAvailable_ = !img.empty();
//     if (textureID_) {
//         glDeleteTextures(1, &textureID_);
//         textureID_ = 0;
//     }
//     if (imageAvailable_) {
//         UploadTexture();
//     }
// }

// // Uploads the image data to an OpenGL texture.
// void OutputNode::UploadTexture() {
//     printf("Debug: OutputNode(%d)::UploadTexture()\n", id_);
//     cv::Mat uploadImage;
//     if (image_.channels() == 3) {
//         // Convert from BGR (default in OpenCV) to RGB
//         cv::cvtColor(image_, uploadImage, cv::COLOR_BGR2RGB);
//     } else {
//         uploadImage = image_;
//     }
    
//     glGenTextures(1, &textureID_);
//     glBindTexture(GL_TEXTURE_2D, textureID_);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//     glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
//     GLenum format = (uploadImage.channels() == 3) ? GL_RGB : GL_RGBA;
//     printf("Debug: uploading texture %d (size %dx%d, format %s)\n",
//            textureID_, uploadImage.cols, uploadImage.rows,
//            (format==GL_RGB ? "RGB" : "RGBA"));
//     glTexImage2D(GL_TEXTURE_2D, 0, format,
//                  uploadImage.cols, uploadImage.rows,
//                  0, format, GL_UNSIGNED_BYTE,
//                  uploadImage.data);
// }

// // Opens a file dialog and saves the current image to disk.
// void OutputNode::SaveImage() {
//     if (!imageAvailable_) return;
    
//     const char* filters[] = { "*.png", "*.jpg", "*.jpeg" };
//     const char* savePath = tinyfd_saveFileDialog("Save Image", "output.png", 3, filters, nullptr);
//     if (!savePath) return; // User cancelled.
    
//     std::string pathStr(savePath);
//     auto dotPos = pathStr.find_last_of('.');
//     std::string ext;
//     if (dotPos != std::string::npos) {
//         ext = pathStr.substr(dotPos + 1);
//         // Convert extension to lowercase.
//         std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
//     }
    
//     std::vector<int> params;
//     if (ext == "jpg" || ext == "jpeg") {
//         params = { cv::IMWRITE_JPEG_QUALITY, quality_ };
//     }
    
//     bool ok = cv::imwrite(pathStr, image_, params);
//     if (!ok) {
//         printf("Error: Failed to save image to %s\n", pathStr.c_str());
//     } else {
//         printf("Saved image to %s\n", pathStr.c_str());
//     }
// }

// // Renders the Output node.
// void OutputNode::Render() {
//     printf("Debug: OutputNode(%d)::Render(), imageAvailable = %d\n", id_, imageAvailable_);
//     ImNodes::BeginNode(id_);
    
//     ImNodes::BeginNodeTitleBar();
//     ImGui::Text("Output Node");
//     ImNodes::EndNodeTitleBar();
    
//     // Declare an input port.
//     ImNodes::BeginInputAttribute(id_ * 10 + 1);
//     ImGui::Text("Image In");
//     ImNodes::EndInputAttribute();
    
//     if (imageAvailable_) {
//         ImGui::Text("Preview:");
//         ImGui::Image((ImTextureID)(intptr_t)textureID_, ImVec2(128,128));
//         ImGui::SliderInt("Quality", &quality_, 1, 100);
//         if (ImGui::Button("Save Image")) {
//             SaveImage();
//         }
//     } else {
//         ImGui::TextDisabled("No image connected.");
//     }
    
//     ImNodes::EndNode();
// }


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

// Constructor
OutputNode::OutputNode(int id)
    : id_(id), textureID_(0), quality_(95), imageAvailable_(false)
{
    printf("Debug: OutputNode(%d) constructed\n", id_);
}

// Accessor for node ID
int OutputNode::GetId() const {
    return id_;
}

// Sets the input image and uploads it as a texture.
void OutputNode::SetInputImage(const cv::Mat &img) {
    printf("Debug: OutputNode(%d)::SetInputImage called. img size = %dx%d\n", id_, img.cols, img.rows);
    image_ = img.clone();
    imageAvailable_ = !img.empty();
    if (textureID_) {
        glDeleteTextures(1, &textureID_);
        textureID_ = 0;
    }
    if (imageAvailable_) {
        UploadTexture();
    }
}

// Uploads the image data to an OpenGL texture.
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
        // Convert grayscale to RGB for compatibility
        cv::cvtColor(image_, uploadImage, cv::COLOR_GRAY2RGB);
        format = GL_RGB;
    } else {
        printf("Error: Unsupported number of channels: %d\n", image_.channels());
        return;
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

// Opens a file dialog and saves the current image to disk.
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

// Renders the Output node.
void OutputNode::Render() {
    printf("Debug: OutputNode(%d)::Render(), imageAvailable = %d\n", id_, imageAvailable_);
    ImNodes::BeginNode(id_);

    ImNodes::BeginNodeTitleBar();
    ImGui::Text("Output Node");
    ImNodes::EndNodeTitleBar();

    ImNodes::BeginInputAttribute(id_ * 10 + 1);
    ImGui::Text("Image In");
    ImNodes::EndInputAttribute();

    if (imageAvailable_) {
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
