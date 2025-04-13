#include "ImageProcessor.h"
#include <stdexcept>

cv::Mat ImageProcessor::LoadImage(const std::string& path) {
    cv::Mat image = cv::imread(path, cv::IMREAD_COLOR);
    if (image.empty()) throw std::runtime_error("Failed to load image: " + path);
    return image;
}

