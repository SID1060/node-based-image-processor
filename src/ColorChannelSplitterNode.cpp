#include "ColorChannelSplitterNode.h"
#include <imgui.h>
#include <imnodes.h>
#include <opencv2/imgproc.hpp>
#include <cstdio>

ColorChannelSplitterNode::ColorChannelSplitterNode(int id)
    : id_(id)
{
    printf("Debug: ColorChannelSplitterNode(%d) constructed\n", id_);
}

#include <opencv2/core.hpp>  // for cv::sum

void ColorChannelSplitterNode::SetInputImage(const cv::Mat& img) {
    if (img.empty()) return;

    // Compute simple hash (sum of all pixels for quick difference check)
    cv::Scalar currentHash = cv::sum(img);

    if (lastHash_ == currentHash) {
        return;  // Image has not changed significantly, skip reprocessing
    }

    inputImage_ = img.clone();
    lastInput_ = inputImage_;
    lastHash_ = currentHash;

    std::vector<cv::Mat> chs;
    cv::split(inputImage_, chs);

    int n = std::min<int>(chs.size(), 4);
    for (int i = 0; i < n; ++i) {
        if (grayscale_) {
            channels_[i] = chs[i];
        } else {
            std::vector<cv::Mat> merge_channels(3, chs[i]);
            cv::merge(merge_channels, channels_[i]);
        }

        printf("Debug: Splitter %d channel %d size %dx%d\n",
               id_, i, channels_[i].cols, channels_[i].rows);
    }

    for (int i = n; i < 4; ++i) {
        channels_[i].release();
    }
}



const cv::Mat& ColorChannelSplitterNode::GetChannelImage(int channel) const {
    static cv::Mat empty;
    if (channel < 0 || channel >= 4) return empty;
    return channels_[channel];
}

void ColorChannelSplitterNode::Render() {
    ImNodes::BeginNode(id_);

    ImNodes::BeginNodeTitleBar();
    ImGui::Text("Channel Splitter");
    ImNodes::EndNodeTitleBar();

    ImNodes::BeginInputAttribute(id_ * 10 + 1);
    ImGui::Text("In");
    ImNodes::EndInputAttribute();

    ImNodes::BeginOutputAttribute(id_ * 10 + 2);
    ImGui::Text("R");
    ImNodes::EndOutputAttribute();

    ImNodes::BeginOutputAttribute(id_ * 10 + 3);
    ImGui::Text("G");
    ImNodes::EndOutputAttribute();

    ImNodes::BeginOutputAttribute(id_ * 10 + 4);
    ImGui::Text("B");
    ImNodes::EndOutputAttribute();

    if (inputImage_.channels() == 4) {
        ImNodes::BeginOutputAttribute(id_ * 10 + 5);
        ImGui::Text("A");
        ImNodes::EndOutputAttribute();
    }

    bool changed = ImGui::Checkbox("Grayscale", &grayscale_);
    if (changed) {
        SetInputImage(inputImage_);
    }

    ImNodes::EndNode();
}


// #include "ColorChannelSplitterNode.h"
// #include <imgui.h>
// #include <imnodes.h>
// #include <opencv2/imgproc.hpp>
// #include <cstdio>

// ColorChannelSplitterNode::ColorChannelSplitterNode(int id)
//     : id_(id)
// {
//     printf("Debug: ColorChannelSplitterNode(%d) constructed\n", id_);
// }

// void ColorChannelSplitterNode::SetInputImage(const cv::Mat& img) {
//     if (img.empty()) {
//         printf("Debug: ColorChannelSplitterNode(%d) received empty image\n", id_);
//         for (int i = 0; i < 3; ++i) channels_[i].release();
//         inputImage_.release();
//         return;
//     }

//     inputImage_ = img.clone();
//     std::vector<cv::Mat> chs;
//     cv::split(inputImage_, chs);

//     if (chs.size() < 3) {
//         printf("Error: ColorChannelSplitterNode(%d) expected 3 channels, got %d\n", id_, (int)chs.size());
//         return;
//     }

//     // OpenCV: chs[0]=Blue, [1]=Green, [2]=Red
//     // Output: channels_[0]=Red, [1]=Green, [2]=Blue
//     int order[3] = {2, 1, 0}; // BGR to RGB
//     for (int i = 0; i < 3; ++i) {
//         int chIndex = order[i];
//         if (grayscale_) {
//             channels_[i] = chs[chIndex]; // 1-channel grayscale
//         } else {
//             // Create 3-channel image with data in correct position
//             std::vector<cv::Mat> merged(3, cv::Mat::zeros(chs[chIndex].size(), CV_8UC1));
//             merged[i] = chs[chIndex]; // Red in merged[0], Green in merged[1], Blue in merged[2]
//             cv::Mat color;
//             cv::merge(merged, color);
//             channels_[i] = color; // 3-channel color
//         }
//         printf("Debug: Splitter %d channel %d size %dx%d\n", id_, i, channels_[i].cols, channels_[i].rows);
//     }
// }

// const cv::Mat& ColorChannelSplitterNode::GetChannelImage(int channel) const {
//     static cv::Mat empty;
//     if (channel < 0 || channel >= 3) {
//         printf("Debug: ColorChannelSplitterNode(%d) invalid channel %d\n", id_, channel);
//         return empty;
//     }
//     return channels_[channel];
// }

// void ColorChannelSplitterNode::Render() {
//     ImNodes::BeginNode(id_);

//     ImNodes::BeginNodeTitleBar();
//     ImGui::Text("Channel Splitter");
//     ImNodes::EndNodeTitleBar();

//     ImNodes::BeginInputAttribute(id_ * 10 + 1);
//     ImGui::Text("In");
//     ImNodes::EndInputAttribute();

//     ImNodes::BeginOutputAttribute(id_ * 10 + 2);
//     ImGui::Text("Red");
//     ImNodes::EndOutputAttribute();

//     ImNodes::BeginOutputAttribute(id_ * 10 + 3);
//     ImGui::Text("Green");
//     ImNodes::EndOutputAttribute();

//     ImNodes::BeginOutputAttribute(id_ * 10 + 4);
//     ImGui::Text("Blue");
//     ImNodes::EndOutputAttribute();

//     bool changed = ImGui::Checkbox("Grayscale", &grayscale_);
//     if (changed && !inputImage_.empty()) {
//         SetInputImage(inputImage_); // Reprocess if grayscale toggle changes
//     }

//     ImNodes::EndNode();
// }