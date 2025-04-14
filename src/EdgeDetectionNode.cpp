#include "EdgeDetectionNode.h"
#include <imgui.h>
#include <imnodes.h>
#include <opencv2/imgproc.hpp>
#include <cstdio>

EdgeDetectionNode::EdgeDetectionNode(int id)
    : id_(id)
{
    printf("Debug: EdgeDetectionNode(%d) constructed\n", id_);
}

void EdgeDetectionNode::SetInputImage(const cv::Mat& img) {
    inputImage_ = img.clone();
    ApplyEdgeDetection();
}

void EdgeDetectionNode::ApplyEdgeDetection() {
    if (inputImage_.empty()) {
        outputImage_.release();
        return;
    }

    cv::Mat gray;
    if (inputImage_.channels() == 3)
        cv::cvtColor(inputImage_, gray, cv::COLOR_BGR2GRAY);
    else
        gray = inputImage_;

    cv::Mat edges;

    if (algorithmType_ == 0) {
        // Sobel
        int k = sobelKernel_;
        cv::Mat gradX, gradY;
        if (sobelX_)
            cv::Sobel(gray, gradX, CV_16S, 1, 0, k);
        if (sobelY_)
            cv::Sobel(gray, gradY, CV_16S, 0, 1, k);

        cv::Mat absX, absY;
        if (sobelX_) cv::convertScaleAbs(gradX, absX);
        if (sobelY_) cv::convertScaleAbs(gradY, absY);

        if (sobelX_ && sobelY_)
            cv::addWeighted(absX, 0.5, absY, 0.5, 0, edges);
        else if (sobelX_)
            edges = absX;
        else
            edges = absY;

    } else {
        // Canny
        cv::Canny(gray, edges, cannyThresh1_, cannyThresh2_, cannyAperture_);
    }

    if (overlay_ && !edges.empty()) {
        // color edges red over original
        cv::Mat colorEdges;
        cv::cvtColor(edges, colorEdges, cv::COLOR_GRAY2BGR);
        outputImage_ = inputImage_.clone();
        // red channel = edges
        std::vector<cv::Mat> chans;
        cv::split(colorEdges, chans);
        std::vector<cv::Mat> dstChans(3);
        // keep original G/B, replace R
        std::vector<cv::Mat> origChans;
        cv::split(outputImage_, origChans);
        dstChans[0] = chans[2];      // R
        dstChans[1] = origChans[1];  // G
        dstChans[2] = origChans[2];  // B
        cv::merge(dstChans, outputImage_);
    } else {
        outputImage_ = edges;
    }

    printf("Debug: EdgeNode(%d) applied %s, overlay=%d\n",
           id_,
           algorithmType_ == 0 ? "Sobel" : "Canny",
           overlay_);
}

void EdgeDetectionNode::Render() {
    ImNodes::BeginNode(id_);
    ImNodes::BeginNodeTitleBar();
    ImGui::Text("Edge Detection");
    ImNodes::EndNodeTitleBar();

    ImNodes::BeginInputAttribute(id_ * 10 + 1);
    ImGui::Text("In");
    ImNodes::EndInputAttribute();

    // Algorithm selector
    const char* algos[] = { "Sobel", "Canny" };
    if (ImGui::Combo("Algo", &algorithmType_, algos, IM_ARRAYSIZE(algos))) {
        ApplyEdgeDetection();
    }

    if (algorithmType_ == 0) {
        ImGui::SliderInt("Kernel Size", &sobelKernel_, 1, 7);
        if (sobelKernel_ % 2 == 0) sobelKernel_ += 1; // force odd
        ImGui::Checkbox("X Gradient", &sobelX_);
        ImGui::Checkbox("Y Gradient", &sobelY_);
    } else {
        ImGui::SliderFloat("Threshold1", &cannyThresh1_, 0.0f, 255.0f);
        ImGui::SliderFloat("Threshold2", &cannyThresh2_, 0.0f, 255.0f);
        ImGui::SliderInt("Aperture", &cannyAperture_, 3, 7);
        if (cannyAperture_ % 2 == 0) cannyAperture_ += 1;
    }

    if (ImGui::Checkbox("Overlay on Original", &overlay_)) {
        ApplyEdgeDetection();
    }

    ImNodes::BeginOutputAttribute(id_ * 10 + 2);
    ImGui::Text("Out");
    ImNodes::EndOutputAttribute();

    ImNodes::EndNode();
}
