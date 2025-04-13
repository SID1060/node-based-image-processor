// #include "BlendNode.h"
// #include <imgui.h>
// #include <imnodes.h>

// BlendNode::BlendNode(int id) : id_(id) {}

// void BlendNode::SetInputA(const cv::Mat& img) {
//     imageA_ = img.clone();
//     BlendImages();
// }

// void BlendNode::SetInputB(const cv::Mat& img) {
//     imageB_ = img.clone();
//     BlendImages();
// }

// const cv::Mat& BlendNode::GetBlendedImage() const {
//     return blended_;
// }

// void BlendNode::BlendImages() {
//     if (imageA_.empty() || imageB_.empty()) return;

//     cv::Mat a, b;
//     cv::resize(imageB_, b, imageA_.size());
//     a = imageA_;

//     switch (blendMode_) {
//         case 0: // Normal blend (linear interpolation)
//             cv::addWeighted(a, 1.0f - opacity_, b, opacity_, 0.0, blended_);
//             break;
//         case 1: // Multiply
//             cv::multiply(a, b, blended_, 1.0 / 255);
//             break;
//         case 2: // Screen
//             blended_ = 255 - ((255 - a).mul(255 - b) / 255);
//             break;
//         case 3: // Overlay
//             blended_ = cv::Mat::zeros(a.size(), a.type());
//             for (int y = 0; y < a.rows; ++y) {
//                 for (int x = 0; x < a.cols; ++x) {
//                     for (int c = 0; c < a.channels(); ++c) {
//                         uchar aVal = a.at<cv::Vec3b>(y, x)[c];
//                         uchar bVal = b.at<cv::Vec3b>(y, x)[c];
//                         uchar result = (aVal < 128)
//                             ? (2 * aVal * bVal / 255)
//                             : (255 - 2 * (255 - aVal) * (255 - bVal) / 255);
//                         blended_.at<cv::Vec3b>(y, x)[c] = result;
//                     }
//                 }
//             }
//             break;
//         case 4: // Difference
//             cv::absdiff(a, b, blended_);
//             break;
//     }
// }


// void BlendNode::Render() {
//     ImNodes::BeginNode(id_);

//     ImNodes::BeginNodeTitleBar();
//     ImGui::Text("Blend Node");
//     ImNodes::EndNodeTitleBar();

//     ImNodes::BeginInputAttribute(id_ * 10 + 1);
//     ImGui::Text("Image A");
//     ImNodes::EndInputAttribute();

//     ImNodes::BeginInputAttribute(id_ * 10 + 2);
//     ImGui::Text("Image B");
//     ImNodes::EndInputAttribute();

//     ImNodes::BeginOutputAttribute(id_ * 10 + 3);
//     ImGui::Text("Blended Output");
//     ImNodes::EndOutputAttribute();

//     const char* modes[] = { "Normal", "Multiply", "Screen", "Overlay", "Difference" };
//     ImGui::Combo("Blend Mode", &blendMode_, modes, IM_ARRAYSIZE(modes));
//     ImGui::SliderFloat("Opacity", &opacity_, 0.0f, 1.0f);

//     ImNodes::EndNode();
// }
