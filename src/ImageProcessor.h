#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H
#include <opencv2/opencv.hpp>
#include <string>

class ImageProcessor {
public:
    cv::Mat LoadImage(const std::string& path);
};

#endif

