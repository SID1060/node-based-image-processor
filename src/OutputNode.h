// #ifndef OUTPUT_NODE_H
// #define OUTPUT_NODE_H

// #include <opencv2/opencv.hpp>
// #include <string>

// class OutputNode {
// public:
//     OutputNode(int id);
//     void Render();
//     void SetInputImage(const cv::Mat& img);

// private:
//     int id_;
//     cv::Mat image_;
//     std::string savePath_;
//     int quality_ = 95;
//     bool imageAvailable_ = false;

//     void SaveImage();
// };

// #endif


// #ifndef OUTPUT_NODE_H
// #define OUTPUT_NODE_H

// #include <opencv2/opencv.hpp>
// #include <string>
// #include <SDL_opengl.h>

// class OutputNode {
// public:
//     OutputNode(int id);
//     int  GetId() const { return id_; }            // ← Add this
//     void Render();
//     void SetInputImage(const cv::Mat& img);

// private:
//     int id_;
//     cv::Mat image_;
//     GLuint textureID_ = 0;
//     int quality_ = 95;
//     bool imageAvailable_ = false;

//     void SaveImage();
//     void UploadTexture();
// };

// #endif

// #ifndef OUTPUT_NODE_H
// #define OUTPUT_NODE_H

// #include <opencv2/opencv.hpp>
// #include <string>
// #include <SDL_opengl.h>

// class OutputNode {
// public:
//     // Constructor takes an integer ID.
//     OutputNode(int id);

//     // Accessor for node ID.
//     int GetId() const;

//     // Renders the node (including a preview image, etc.)
//     void Render();

//     // Sets the input image and uploads it as a texture.
//     void SetInputImage(const cv::Mat &img);

// private:
//     int id_;
//     cv::Mat image_;
//     GLuint textureID_;
//     int quality_;
//     bool imageAvailable_;

//     // Saves the image to disk using a file dialog.
//     void SaveImage();

//     // Uploads the cv::Mat image data to an OpenGL texture.
//     void UploadTexture();
// };

// #endif


#ifndef OUTPUT_NODE_H
#define OUTPUT_NODE_H

#include <opencv2/core.hpp>

class OutputNode {
public:
    OutputNode(int id);
    int GetId() const;

    void SetInputImage(const cv::Mat& img);
    void Render();

private:
    int id_;
    cv::Mat image_;
    unsigned int textureID_;
    int quality_;
    bool imageAvailable_;

    void UploadTexture();
    void SaveImage();
};

#endif
