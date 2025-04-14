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
//     inputImage_ = img.clone();
//     if (inputImage_.empty()) {
//         printf("Debug: Splitter %d got empty input\n", id_);
//         return;
//     }

//     std::vector<cv::Mat> chs;
//     cv::split(inputImage_, chs);
//     int n = std::min<int>(chs.size(), 4);
//     for (int i = 0; i < n; ++i) {
//         if (grayscale_) {
//             channels_[i] = chs[i];
//         } else {
//             cv::cvtColor(chs[i], channels_[i], cv::COLOR_GRAY2BGR);
//         }
//         printf("Debug: Splitter %d channel %d size %dx%d\n",
//                id_, i, channels_[i].cols, channels_[i].rows);
//     }

//     for (int i = n; i < 4; ++i) {
//         channels_[i].release();
//     }
// }

// const cv::Mat& ColorChannelSplitterNode::GetChannelImage(int channel) const {
//     static cv::Mat empty;
//     if (channel < 0 || channel >= 4) return empty;
//     return channels_[channel];
// }

// cv::Mat ColorChannelSplitterNode::GetOutputImage() const {
//     return GetChannelImage(selectedChannel_);
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
//     ImGui::Text("R");
//     if (ImGui::IsItemClicked()) selectedChannel_ = 0;
//     ImNodes::EndOutputAttribute();

//     ImNodes::BeginOutputAttribute(id_ * 10 + 3);
//     ImGui::Text("G");
//     if (ImGui::IsItemClicked()) selectedChannel_ = 1;
//     ImNodes::EndOutputAttribute();

//     ImNodes::BeginOutputAttribute(id_ * 10 + 4);
//     ImGui::Text("B");
//     if (ImGui::IsItemClicked()) selectedChannel_ = 2;
//     ImNodes::EndOutputAttribute();

//     if (inputImage_.channels() == 4) {
//         ImNodes::BeginOutputAttribute(id_ * 10 + 5);
//         ImGui::Text("A");
//         if (ImGui::IsItemClicked()) selectedChannel_ = 3;
//         ImNodes::EndOutputAttribute();
//     }

//     ImGui::Checkbox("Grayscale", &grayscale_);
//     if (!inputImage_.empty() && ImGui::IsItemDeactivatedAfterEdit()) {
//         SetInputImage(inputImage_);
//     }

//     ImGui::Text("Preview: %s", selectedChannel_ == 0 ? "R" :
//                                selectedChannel_ == 1 ? "G" :
//                                selectedChannel_ == 2 ? "B" : "A");

//     ImNodes::EndNode();
// }
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
//     inputImage_ = img.clone();
//     if (inputImage_.empty()) {
//         printf("Debug: Splitter %d got empty input\n", id_);
//         return;
//     }

//     std::vector<cv::Mat> chs;
//     cv::split(inputImage_, chs);
//     int n = std::min<int>(chs.size(), 4);
//     for (int i = 0; i < n; ++i) {
//         if (grayscale_) {
//             channels_[i] = chs[i];
//         } else {
//             std::vector<cv::Mat> merge_channels(3, chs[i]);
//             cv::merge(merge_channels, channels_[i]);
//         }
//         printf("Debug: Splitter %d channel %d size %dx%d\n",
//                id_, i, channels_[i].cols, channels_[i].rows);
//     }

//     for (int i = n; i < 4; ++i) {
//         channels_[i].release();
//     }
// }

// const cv::Mat& ColorChannelSplitterNode::GetChannelImage(int channel) const {
//     static cv::Mat empty;
//     if (channel < 0 || channel >= 4) return empty;
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
//     ImGui::Text("R");
//     ImNodes::EndOutputAttribute();

//     ImNodes::BeginOutputAttribute(id_ * 10 + 3);
//     ImGui::Text("G");
//     ImNodes::EndOutputAttribute();

//     ImNodes::BeginOutputAttribute(id_ * 10 + 4);
//     ImGui::Text("B");
//     ImNodes::EndOutputAttribute();

//     if (inputImage_.channels() == 4) {
//         ImNodes::BeginOutputAttribute(id_ * 10 + 5);
//         ImGui::Text("A");
//         ImNodes::EndOutputAttribute();
//     }

//     ImGui::Checkbox("Grayscale", &grayscale_);
//     if (!inputImage_.empty() && ImGui::IsItemDeactivatedAfterEdit()) {
//         SetInputImage(inputImage_);
//     }

//     ImNodes::EndNode();
// }


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
//     // Optimization: skip if image is unchanged
//     if (!lastInput_.empty() && cv::norm(img, lastInput_, cv::NORM_L2) == 0) {
//         printf("Debug: Splitter %d received identical image, skipping\n", id_);
//         return;
//     }

//     inputImage_ = img.clone();
//     lastInput_ = img.clone();  // Save for comparison next time

//     if (inputImage_.empty()) {
//         printf("Debug: Splitter %d got empty input\n", id_);
//         return;
//     }

//     std::vector<cv::Mat> chs;
//     cv::split(inputImage_, chs);
//     int n = std::min<int>(chs.size(), 4);
//     for (int i = 0; i < n; ++i) {
//         if (grayscale_) {
//             channels_[i] = chs[i];
//         } else {
//             std::vector<cv::Mat> merge_channels(3, chs[i]);
//             cv::merge(merge_channels, channels_[i]);
//         }
//         printf("Debug: Splitter %d channel %d size %dx%d\n",
//                id_, i, channels_[i].cols, channels_[i].rows);
//     }

//     for (int i = n; i < 4; ++i) {
//         channels_[i].release();
//     }
// }

// const cv::Mat& ColorChannelSplitterNode::GetChannelImage(int channel) const {
//     static cv::Mat empty;
//     if (channel < 0 || channel >= 4) return empty;
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
//     ImGui::Text("R");
//     ImNodes::EndOutputAttribute();

//     ImNodes::BeginOutputAttribute(id_ * 10 + 3);
//     ImGui::Text("G");
//     ImNodes::EndOutputAttribute();

//     ImNodes::BeginOutputAttribute(id_ * 10 + 4);
//     ImGui::Text("B");
//     ImNodes::EndOutputAttribute();

//     if (inputImage_.channels() == 4) {
//         ImNodes::BeginOutputAttribute(id_ * 10 + 5);
//         ImGui::Text("A");
//         ImNodes::EndOutputAttribute();
//     }

//     ImGui::Checkbox("Grayscale", &grayscale_);
//     if (!inputImage_.empty() && ImGui::IsItemDeactivatedAfterEdit()) {
//         SetInputImage(inputImage_);
//     }

//     ImNodes::EndNode();
// }


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

