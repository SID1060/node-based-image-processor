#ifndef NOISE_NODE_H
#define NOISE_NODE_H

#include <opencv2/opencv.hpp>

class NoiseNode {
public:
    NoiseNode(int id);
    int  GetId() const { return id_; }

    // Draw the ImGui/ImNodes UI
    void Render();
    // Return the generated noise image
    cv::Mat GetOutputImage() const;

private:
    int id_;
    int outputAttr_;

    // Noise parameters
    int   width_       = 256;
    int   height_      = 256;
    float scale_       = 20.0f;
    int   octaves_     = 4;
    float persistence_ = 0.5f;
    int   noiseType_   = 0; // 0 = Perlin, 1 = Simplex, 2 = Worley

    mutable cv::Mat noiseImage_;

    // Regenerate on parameter change
    void GenerateNoise() const;
    cv::Mat GeneratePerlin() const;
    cv::Mat GenerateSimplex() const;
    cv::Mat GenerateWorley() const;
};

#endif // NOISE_NODE_H
