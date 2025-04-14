// #include "ThresholdNode.h"
// #include <imgui.h>
// #include <imnodes.h>

// ThresholdNode::ThresholdNode(int id)
//     : id_(id), thresholdType_(0), threshValue_(128.0f), maxValue_(255.0f), adaptiveMethod_(0)
// {}

// void ThresholdNode::SetInputImage(const cv::Mat& img) {
//     inputImage_ = img.clone();
//     ApplyThreshold();
// }

// const cv::Mat& ThresholdNode::GetOutputImage() const {
//     return outputImage_;
// }

// void ThresholdNode::Render() {
//     ImNodes::BeginNode(id_);

//     ImNodes::BeginNodeTitleBar();
//     ImGui::Text("Threshold");
//     ImNodes::EndNodeTitleBar();

//     ImNodes::BeginInputAttribute(id_ * 10 + 1);
//     ImGui::Text("Input");
//     ImNodes::EndInputAttribute();

//     ImGui::Text("Type:");
//     const char* types[] = { "Binary", "Otsu", "Adaptive" };
//     if (ImGui::Combo("##type", &thresholdType_, types, IM_ARRAYSIZE(types))) {
//         ApplyThreshold();
//     }

//     if (thresholdType_ == 0) {
//         if (ImGui::SliderFloat("Threshold", &threshValue_, 0.0f, 255.0f)) {
//             ApplyThreshold();
//         }
//         if (ImGui::SliderFloat("Max Value", &maxValue_, 0.0f, 255.0f)) {
//             ApplyThreshold();
//         }
//     } else if (thresholdType_ == 2) {
//         const char* adaptiveTypes[] = { "Mean", "Gaussian" };
//         if (ImGui::Combo("Adaptive Method", &adaptiveMethod_, adaptiveTypes, IM_ARRAYSIZE(adaptiveTypes))) {
//             ApplyThreshold();
//         }
//     }

//     if (!inputImage_.empty()) {
//         cv::Mat gray;
//         cv::cvtColor(inputImage_, gray, cv::COLOR_BGR2GRAY);
//         DrawHistogram(gray);
//     }

//     ImNodes::BeginOutputAttribute(id_ * 10 + 2);
//     ImGui::Text("Output");
//     ImNodes::EndOutputAttribute();

//     ImNodes::EndNode();
// }

// void ThresholdNode::ApplyThreshold() {
//     if (inputImage_.empty()) return;

//     cv::Mat gray;
//     cv::cvtColor(inputImage_, gray, cv::COLOR_BGR2GRAY);

//     if (thresholdType_ == 0) {
//         cv::threshold(gray, outputImage_, threshValue_, maxValue_, cv::THRESH_BINARY);
//     } else if (thresholdType_ == 1) {
//         cv::threshold(gray, outputImage_, 0, maxValue_, cv::THRESH_BINARY | cv::THRESH_OTSU);
//     } else {
//         int method = adaptiveMethod_ == 0 ? cv::ADAPTIVE_THRESH_MEAN_C : cv::ADAPTIVE_THRESH_GAUSSIAN_C;
//         cv::adaptiveThreshold(gray, outputImage_, maxValue_, method, cv::THRESH_BINARY, 11, 2);
//     }
// }

// void ThresholdNode::DrawHistogram(const cv::Mat& gray) {
//     int histSize = 256;
//     float range[] = { 0, 256 };
//     const float* histRange = { range };
//     cv::Mat hist;

//     cv::calcHist(&gray, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange);
//     float maxVal = *std::max_element(hist.begin<float>(), hist.end<float>());

//     ImGui::PlotHistogram("Histogram", hist.ptr<float>(), histSize, 0, nullptr, 0.0f, maxVal, ImVec2(200, 100));
// }


#include "ThresholdNode.h"
#include <imgui.h>
#include <imnodes.h>
#include <algorithm>
#include <vector>

ThresholdNode::ThresholdNode(int id)
    : id_(id), thresholdType_(0), threshValue_(128.0f), maxValue_(255.0f), adaptiveMethod_(0)
{}

void ThresholdNode::SetInputImage(const cv::Mat& img) {
    inputImage_ = img.clone();
    ApplyThreshold();
}

const cv::Mat& ThresholdNode::GetOutputImage() const {
    return outputImage_;
}

void ThresholdNode::Render() {
    ImNodes::BeginNode(id_);

    ImNodes::BeginNodeTitleBar();
    ImGui::Text("Threshold");
    ImNodes::EndNodeTitleBar();

    ImNodes::BeginInputAttribute(id_ * 10 + 1);
    ImGui::Text("Input");
    ImNodes::EndInputAttribute();

    ImGui::Text("Type:");
    const char* types[] = { "Binary", "Otsu", "Adaptive" };
    if (ImGui::Combo("##type", &thresholdType_, types, IM_ARRAYSIZE(types))) {
        ApplyThreshold();
    }

    if (thresholdType_ == 0) {
        if (ImGui::SliderFloat("Threshold", &threshValue_, 0.0f, 255.0f)) {
            ApplyThreshold();
        }
        if (ImGui::SliderFloat("Max Value", &maxValue_, 0.0f, 255.0f)) {
            ApplyThreshold();
        }
    } else if (thresholdType_ == 2) {
        const char* adaptiveTypes[] = { "Mean", "Gaussian" };
        if (ImGui::Combo("Adaptive Method", &adaptiveMethod_, adaptiveTypes, IM_ARRAYSIZE(adaptiveTypes))) {
            ApplyThreshold();
        }
    }

    // Show histogram (grayscale only)
    if (!inputImage_.empty()) {
        cv::Mat gray;
        cv::cvtColor(inputImage_, gray, cv::COLOR_BGR2GRAY);
        DrawHistogram(gray);
    }

    ImNodes::BeginOutputAttribute(id_ * 10 + 2);
    ImGui::Text("Output");
    ImNodes::EndOutputAttribute();

    ImNodes::EndNode();
}

void ThresholdNode::ApplyThreshold() {
    if (inputImage_.empty()) return;

    cv::Mat gray;
    cv::cvtColor(inputImage_, gray, cv::COLOR_BGR2GRAY);

    if (thresholdType_ == 0) {
        cv::threshold(gray, outputImage_, threshValue_, maxValue_, cv::THRESH_BINARY);
    } else if (thresholdType_ == 1) {
        cv::threshold(gray, outputImage_, 0, maxValue_, cv::THRESH_BINARY | cv::THRESH_OTSU);
    } else {
        int method = adaptiveMethod_ == 0 ? cv::ADAPTIVE_THRESH_MEAN_C : cv::ADAPTIVE_THRESH_GAUSSIAN_C;
        cv::adaptiveThreshold(gray, outputImage_, maxValue_, method, cv::THRESH_BINARY, 11, 2);
    }
}

void ThresholdNode::DrawHistogram(const cv::Mat& gray) {
    int histSize = 256;
    float range[] = { 0, 256 };
    const float* histRange = { range };
    cv::Mat hist;

    cv::calcHist(&gray, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange);
    double maxVal = 0;
    cv::minMaxLoc(hist, 0, &maxVal);

    std::vector<float> histData(histSize);
    for (int i = 0; i < histSize; ++i) {
        histData[i] = hist.at<float>(i);
    }

    ImGui::PlotHistogram("Histogram", histData.data(), histSize, 0, nullptr, 0.0f, static_cast<float>(maxVal), ImVec2(200, 100));
}
