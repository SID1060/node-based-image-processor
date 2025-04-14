// #include "NodeEditor.h"
// #include <imgui.h>
// #include <imnodes.h>
// #include <stdio.h>

// NodeEditor::NodeEditor() {
//     printf("Debug: NodeEditor constructor called\n");
//     nextNodeId_ = 1;
//     inputNodes_.clear();
//     outputNodes_.clear();
//     blendNodes_.clear();
// }

// void NodeEditor::Render() {
//     printf("Debug: Entering NodeEditor::Render\n");

//     ImGui::Begin("Add Nodes");

//     if (ImGui::Button("Add Input Node")) {
//         inputNodes_.push_back(std::make_unique<ImageInputNode>(nextNodeId_++));
//         printf("Debug: Added Input Node\n");
//     }

//     if (ImGui::Button("Add Output Node")) {
//         outputNodes_.push_back(std::make_unique<OutputNode>(nextNodeId_++));
//         printf("Debug: Added Output Node\n");
//     }

//     if (ImGui::Button("Add Blend Node")) {
//         blendNodes_.push_back(std::make_unique<BlendNode>(nextNodeId_++));
//         printf("Debug: Added Blend Node\n");
//     }

//     ImGui::End();

//     // Render all node types
//     for (auto& node : inputNodes_) {
//         node->Render();
//     }

//     for (auto& node : outputNodes_) {
//         node->Render();
//     }

//     for (auto& node : blendNodes_) {
//         node->Render();
//     }

//     printf("Debug: Leaving NodeEditor::Render\n");
// }
// #include "NodeEditor.h"
// #include <imgui.h>
// #include <imnodes.h>
// #include <stdio.h>
// #include <opencv2/opencv.hpp> // for cv::Mat

// NodeEditor::NodeEditor()
//     : nextNodeId_(1)
//     , nextLinkId_(1)
// {}

// void NodeEditor::Render() {
//     // --- UI to add nodes ---
//     ImGui::Begin("Add Nodes");
//     if (ImGui::Button("Add Input Node")) {
//         inputNodes_.push_back(std::make_unique<ImageInputNode>(nextNodeId_++));
//     }
//     if (ImGui::Button("Add Output Node")) {
//         outputNodes_.push_back(std::make_unique<OutputNode>(nextNodeId_++));
//     }
//     ImGui::End();

//     // --- Node editor canvas ---
//     ImNodes::BeginNodeEditor();

//     // Render nodes
//     for (auto& in  : inputNodes_)  in->Render();
//     for (auto& out : outputNodes_) out->Render();


//     // Draw existing links
//     for (auto& link : links_) {
//         ImNodes::Link(link.id, link.start_attr, link.end_attr);
//     }

//     ImNodes::EndNodeEditor();

//     // --- Handle new link creation (must be *after* EndNodeEditor) ---
//     int start_attr, end_attr;
//     if (ImNodes::IsLinkCreated(&start_attr, &end_attr)) {
//         printf("Debug: Link created attrs %d -> %d\n", start_attr, end_attr);
//         links_.push_back({ nextLinkId_++, start_attr, end_attr });

//         int startNodeId = start_attr / 10;
//         int endNodeId   = end_attr   / 10;
//         printf("Debug: Link maps node %d -> node %d\n", startNodeId, endNodeId);

//         cv::Mat img;
//         for (auto& in : inputNodes_) {
//             if (in->GetId() == startNodeId) {
//                 img = in->GetImage();
//                 printf("Debug: Found input node %d, img size %dx%d\n",
//                        startNodeId, img.cols, img.rows);
//                 break;
//             }
//         }
//         for (auto& out : outputNodes_) {
//             if (out->GetId() == endNodeId) {
//                 printf("Debug: Setting image on output node %d\n", endNodeId);
//                 out->SetInputImage(img);
//                 break;
//             }
//         }
//     }

// }
// #include "NodeEditor.h"
// #include <imgui.h>
// #include <imnodes.h>
// #include <opencv2/opencv.hpp>
// #include <map>
// #include <cstdio>

// NodeEditor::NodeEditor()
//     : nextNodeId_(1)
//     , nextLinkId_(1)
// {}

// void NodeEditor::Render() {
//     // 1) UI to add nodes
//     ImGui::Begin("Add Nodes");
//     if (ImGui::Button("Add Input Node")) {
//         inputNodes_.push_back(std::make_unique<ImageInputNode>(nextNodeId_++));
//     }
//     if (ImGui::Button("Add Brightness/Contrast")) {
//         bcNodes_.push_back(std::make_unique<BrightnessContrastNode>(nextNodeId_++));
//     }
//     if (ImGui::Button("Add Channel Splitter")) {
//         splitterNodes_.push_back(std::make_unique<ColorChannelSplitterNode>(nextNodeId_++));
//     }
//     if (ImGui::Button("Add Output Node")) {
//         outputNodes_.push_back(std::make_unique<OutputNode>(nextNodeId_++));
//     }
//     ImGui::End();

//     // 2) Node editor canvas
//     ImNodes::BeginNodeEditor();

//     // Render all nodes
//     for (auto& n : inputNodes_)      n->Render();
//     for (auto& n : bcNodes_)         n->Render();
//     for (auto& n : splitterNodes_)   n->Render();
//     for (auto& n : outputNodes_)     n->Render();

//     // Draw links
//     for (auto& link : links_) {
//         ImNodes::Link(link.id, link.start_attr, link.end_attr);
//     }

//     ImNodes::EndNodeEditor();

//     // 3) Detect new links
//     int start_attr, end_attr;
//     if (ImNodes::IsLinkCreated(&start_attr, &end_attr)) {
//         links_.push_back({ nextLinkId_++, start_attr, end_attr });
//         printf("Debug: Link created %d→%d\n", start_attr, end_attr);
//     }

//     // 4) Propagate images through the graph
//     EvaluateGraph();
// }

// void NodeEditor::EvaluateGraph() {
//     std::map<int, cv::Mat> outputs;

//     // 1) Seed with Input nodes
//     for (auto& in : inputNodes_) {
//         cv::Mat img = in->GetImage();
//         if (!img.empty()) {
//             outputs[in->GetId()] = img;
//             printf("Debug: Eval seed Input %d size %dx%d\n",
//                    in->GetId(), img.cols, img.rows);
//         }
//     }

//     bool progress = true;
//     while (progress) {
//         progress = false;

//         for (auto& link : links_) {
//             int s = link.start_attr / 10;
//             int e = link.end_attr   / 10;

//             // Only proceed if we have an output for s, and haven't done e yet
//             auto it = outputs.find(s);
//             if (it == outputs.end() || outputs.count(e)) continue;

//             cv::Mat img = it->second;

//             // 2a) Brightness/Contrast node
//             for (auto& bc : bcNodes_) {
//                 if (bc->GetId() == e) {
//                     bc->SetInputImage(img);
//                     outputs[e] = bc->GetOutputImage();
//                     printf("Debug: Eval BC %d from %d\n", e, s);
//                     progress = true;
//                 }
//             }

//             // 2b) Channel Splitter node
//             for (auto& splitter : splitterNodes_) {
//                 if (splitter->GetId() == e) {
//                     splitter->SetInputImage(img);
//                     printf("Debug: Eval Splitter %d from %d\n", e, s);
//                     progress = true;
//                 }

//                 // Use channel index from attribute ID
//                 int outputAttr = link.start_attr;
//                 int splitterId = outputAttr / 10;
//                 int channelIndex = outputAttr - splitterId * 10 - 2;
//                 if (splitter->GetId() == splitterId) {
//                     outputs[e] = splitter->GetChannelImage(channelIndex);
//                     printf("Debug: Splitter %d output channel %d → node %d\n", splitterId, channelIndex, e);
//                 }
//             }

//             // 2c) Output node
//             for (auto& out : outputNodes_) {
//                 if (out->GetId() == e) {
//                     out->SetInputImage(img);
//                     outputs[e] = img; // mark as visited
//                     printf("Debug: Eval Output %d from %d\n", e, s);
//                     progress = true;
//                 }
//             }
//         }
//     }
// }

// #include "NodeEditor.h"
// #include <imgui.h>
// #include <imnodes.h>
// #include <opencv2/opencv.hpp>
// #include <map>
// #include <cstdio>

// NodeEditor::NodeEditor()
//     : nextNodeId_(1)
//     , nextLinkId_(1)
// {}

// void NodeEditor::Render() {
//     // 1) UI to add nodes
//     ImGui::Begin("Add Nodes");
//     if (ImGui::Button("Add Input Node")) {
//         inputNodes_.push_back(std::make_unique<ImageInputNode>(nextNodeId_++));
//     }
//     if (ImGui::Button("Add Brightness/Contrast")) {
//         bcNodes_.push_back(std::make_unique<BrightnessContrastNode>(nextNodeId_++));
//     }
//     if (ImGui::Button("Add Channel Splitter")) {
//         splitterNodes_.push_back(std::make_unique<ColorChannelSplitterNode>(nextNodeId_++));
//     }
//     if (ImGui::Button("Add Blur Node")) {
//         blurNodes_.push_back(std::make_unique<BlurNode>(nextNodeId_++));
//     }
//     if (ImGui::Button("Add Threshold")) {
//         thresholdNodes_.push_back(std::make_unique<ThresholdNode>(nextNodeId_++));
//     }
//     if (ImGui::Button("Add Edge Node")) {
//         edgeNodes_.push_back(std::make_unique<EdgeDetectionNode>(nextNodeId_++));
//     }    
//     if (ImGui::Button("Add Output Node")) {
//         outputNodes_.push_back(std::make_unique<OutputNode>(nextNodeId_++));
//     }
//     ImGui::End();

//     // 2) Node editor canvas
//     ImNodes::BeginNodeEditor();

//     // Render all nodes
//     for (auto& n : inputNodes_)      n->Render();
//     for (auto& n : bcNodes_)         n->Render();
//     for (auto& n : splitterNodes_)   n->Render();
//     for (auto& n : blurNodes_)       n->Render();
//     for (auto& node : thresholdNodes_) node->Render();
//     for (auto& n : edgeNodes_) n->Render();
//     for (auto& n : outputNodes_)     n->Render();

//     // Draw links
//     for (auto& link : links_) {
//         ImNodes::Link(link.id, link.start_attr, link.end_attr);
//     }

//     ImNodes::EndNodeEditor();

//     // 3) Detect new links
//     int start_attr, end_attr;
//     if (ImNodes::IsLinkCreated(&start_attr, &end_attr)) {
//         links_.push_back({ nextLinkId_++, start_attr, end_attr });
//         printf("Debug: Link created %d→%d\n", start_attr, end_attr);
//     }

//     // 4) Propagate images through the graph
//     EvaluateGraph();
// }

// void NodeEditor::EvaluateGraph() {
//     std::map<int, cv::Mat> outputs;

//     // 1) Seed with Input nodes
//     for (auto& in : inputNodes_) {
//         cv::Mat img = in->GetImage();
//         if (!img.empty()) {
//             outputs[in->GetId()] = img;
//             printf("Debug: Eval seed Input %d size %dx%d\n",
//                    in->GetId(), img.cols, img.rows);
//         }
//     }

//     bool progress = true;
//     while (progress) {
//         progress = false;

//         for (auto& link : links_) {
//             int s = link.start_attr / 10;
//             int e = link.end_attr   / 10;

//             // Only proceed if we have an output for s, and haven't done e yet
//             auto it = outputs.find(s);
//             if (it == outputs.end() || outputs.count(e)) continue;

//             cv::Mat img = it->second;

//             // 2a) Brightness/Contrast node
//             for (auto& bc : bcNodes_) {
//                 if (bc->GetId() == e) {
//                     bc->SetInputImage(img);
//                     outputs[e] = bc->GetOutputImage();
//                     printf("Debug: Eval BC %d from %d\n", e, s);
//                     progress = true;
//                 }
//             }

//             // 2b) Channel Splitter node
//             for (auto& splitter : splitterNodes_) {
//                 if (splitter->GetId() == e) {
//                     splitter->SetInputImage(img);
//                     printf("Debug: Eval Splitter %d from %d\n", e, s);
//                     progress = true;
//                 }

//                 int outputAttr = link.start_attr;
//                 int splitterId = outputAttr / 10;
//                 int channelIndex = outputAttr - splitterId * 10 - 2;
//                 if (splitter->GetId() == splitterId) {
//                     outputs[e] = splitter->GetChannelImage(channelIndex);
//                     printf("Debug: Splitter %d output channel %d → node %d\n", splitterId, channelIndex, e);
//                 }
//             }

//             // 2c) Blur node
//             for (auto& blur : blurNodes_) {
//                 if (blur->GetId() == e) {
//                     blur->SetInputImage(img);
//                     outputs[e] = blur->GetOutputImage();
//                     printf("Debug: Eval Blur %d from %d\n", e, s);
//                     progress = true;
//                 }
//             }
//             //2d) thresholdNode
//             for (auto& thresh : thresholdNodes_) {
//                 if (thresh->GetId() == e) {
//                     thresh->SetInputImage(img);
//                     outputs[e] = thresh->GetOutputImage();
//                     printf("Debug: Eval Threshold %d from %d\n", e, s);
//                     progress = true;
//                 }
//             }
//             //2e) EdgeDetection Node
//             for (auto& ed : edgeNodes_) {
//                 if (ed->GetId() == e) {
//                     ed->SetInputImage(img);
//                     outputs[e] = ed->GetOutputImage();
//                     printf("Debug: Eval Edge %d from %d\n", e, s);
//                     progress = true;
//                 }
//             }
//             // 2f) Output node
//             for (auto& out : outputNodes_) {
//                 if (out->GetId() == e) {
//                     out->SetInputImage(img);
//                     outputs[e] = img; // mark as visited
//                     printf("Debug: Eval Output %d from %d\n", e, s);
//                     progress = true;
//                 }
//             }
//         }
//     }
// }


// #include "NodeEditor.h"
// #include <imgui.h>
// #include <imnodes.h>
// #include <opencv2/opencv.hpp>
// #include <map>
// #include <cstdio>

// // Include all custom nodes
// // #include "ImageInputNode.h"
// #include "OutputNode.h"
// #include "BrightnessContrastNode.h"
// #include "ColorChannelSplitterNode.h"
// #include "BlurNode.h"
// #include "ThresholdNode.h"
// #include "EdgeDetectionNode.h"
// #include "ConvolutionNode.h" // 
// #include "NoiseNode.h"


// NodeEditor::NodeEditor()
//     : nextNodeId_(1)
//     , nextLinkId_(1)
// {}

// void NodeEditor::Render() {
//     ImGui::Begin("Add Nodes");
//     if (ImGui::Button("Add Input Node")) {
//         inputNodes_.push_back(std::make_unique<ImageInputNode>(nextNodeId_++));
//     }
//     if (ImGui::Button("Add Brightness/Contrast")) {
//         bcNodes_.push_back(std::make_unique<BrightnessContrastNode>(nextNodeId_++));
//     }
//     if (ImGui::Button("Add Channel Splitter")) {
//         splitterNodes_.push_back(std::make_unique<ColorChannelSplitterNode>(nextNodeId_++));
//     }
//     if (ImGui::Button("Add Blur Node")) {
//         blurNodes_.push_back(std::make_unique<BlurNode>(nextNodeId_++));
//     }
//     if (ImGui::Button("Add Threshold")) {
//         thresholdNodes_.push_back(std::make_unique<ThresholdNode>(nextNodeId_++));
//     }
//     if (ImGui::Button("Add Edge Node")) {
//         edgeNodes_.push_back(std::make_unique<EdgeDetectionNode>(nextNodeId_++));
//     }
//     if (ImGui::Button("Add Convolution Node")) {
//         convNodes_.push_back(std::make_unique<ConvolutionNode>(nextNodeId_++)); // ✅ NEW
//     }
//     if (ImGui::Button("Add Noise Node")) {
//         noiseNodes_.push_back(std::make_unique<NoiseNode>(nextNodeId_++));
//     }    
//     if (ImGui::Button("Add Output Node")) {
//         outputNodes_.push_back(std::make_unique<OutputNode>(nextNodeId_++));
//     }
//     ImGui::End();

//     ImNodes::BeginNodeEditor();

//     for (auto& n : inputNodes_)      n->Render();
//     for (auto& n : bcNodes_)         n->Render();
//     for (auto& n : splitterNodes_)   n->Render();
//     for (auto& n : blurNodes_)       n->Render();
//     for (auto& n : thresholdNodes_)  n->Render();
//     for (auto& n : edgeNodes_)       n->Render();
//     for (auto& n : convNodes_)       n->Render(); 
//     for (auto& n : noiseNodes_) n->Render();
//     for (auto& n : outputNodes_)     n->Render();

//     for (auto& link : links_) {
//         ImNodes::Link(link.id, link.start_attr, link.end_attr);
//     }

//     ImNodes::EndNodeEditor();

//     int start_attr, end_attr;
//     if (ImNodes::IsLinkCreated(&start_attr, &end_attr)) {
//         links_.push_back({ nextLinkId_++, start_attr, end_attr });
//         printf("Debug: Link created %d→%d\n", start_attr, end_attr);
//     }

//     EvaluateGraph();
// }

// void NodeEditor::EvaluateGraph() {
//     std::map<int, cv::Mat> outputs;

//     for (auto& in : inputNodes_) {
//         cv::Mat img = in->GetImage();
//         if (!img.empty()) {
//             outputs[in->GetId()] = img;
//             printf("Debug: Eval seed Input %d size %dx%d\n",
//                    in->GetId(), img.cols, img.rows);
//         }
//     }

//     bool progress = true;
//     while (progress) {
//         progress = false;

//         for (auto& link : links_) {
//             int s = link.start_attr / 10;
//             int e = link.end_attr   / 10;

//             auto it = outputs.find(s);
//             if (it == outputs.end() || outputs.count(e)) continue;

//             cv::Mat img = it->second;

//             for (auto& bc : bcNodes_) {
//                 if (bc->GetId() == e) {
//                     bc->SetInputImage(img);
//                     outputs[e] = bc->GetOutputImage();
//                     printf("Debug: Eval BC %d from %d\n", e, s);
//                     progress = true;
//                 }
//             }

//             for (auto& splitter : splitterNodes_) {
//                 if (splitter->GetId() == e) {
//                     splitter->SetInputImage(img);
//                     printf("Debug: Eval Splitter %d from %d\n", e, s);
//                     progress = true;
//                 }

//                 int outputAttr = link.start_attr;
//                 int splitterId = outputAttr / 10;
//                 int channelIndex = outputAttr - splitterId * 10 - 2;
//                 if (splitter->GetId() == splitterId) {
//                     outputs[e] = splitter->GetChannelImage(channelIndex);
//                     printf("Debug: Splitter %d output channel %d → node %d\n", splitterId, channelIndex, e);
//                 }
//             }

//             for (auto& blur : blurNodes_) {
//                 if (blur->GetId() == e) {
//                     blur->SetInputImage(img);
//                     outputs[e] = blur->GetOutputImage();
//                     printf("Debug: Eval Blur %d from %d\n", e, s);
//                     progress = true;
//                 }
//             }

//             for (auto& thresh : thresholdNodes_) {
//                 if (thresh->GetId() == e) {
//                     thresh->SetInputImage(img);
//                     outputs[e] = thresh->GetOutputImage();
//                     printf("Debug: Eval Threshold %d from %d\n", e, s);
//                     progress = true;
//                 }
//             }

//             for (auto& ed : edgeNodes_) {
//                 if (ed->GetId() == e) {
//                     ed->SetInputImage(img);
//                     outputs[e] = ed->GetOutputImage();
//                     printf("Debug: Eval Edge %d from %d\n", e, s);
//                     progress = true;
//                 }
//             }

//             for (auto& conv : convNodes_) {
//                 if (conv->GetId() == e) {
//                     conv->SetInputImage(img);
//                     outputs[e] = conv->GetOutputImage();
//                     printf("Debug: Eval Convolution %d from %d\n", e, s);
//                     progress = true;
//                 }
//             }
//             for (auto& noise : noiseNodes_) {
//                 outputs[noise->GetId()] = noise->GetOutputImage();
//                 printf("Debug: Eval seed Noise %d size %dx%d\n",
//                        noise->GetId(),
//                        noise->GetOutputImage().cols,
//                        noise->GetOutputImage().rows);
//             }
//             for (auto& out : outputNodes_) {
//                 if (out->GetId() == e) {
//                     out->SetInputImage(img);
//                     outputs[e] = img;
//                     printf("Debug: Eval Output %d from %d\n", e, s);
//                     progress = true;
//                 }
//             }
//         }
//     }
// }
#include "NodeEditor.h"
#include <imgui.h>
#include <imnodes.h>
#include <opencv2/opencv.hpp>
#include <map>
#include <cstdio>

// Include all custom nodes
#include "BrightnessContrastNode.h"
#include "ColorChannelSplitterNode.h"
#include "BlurNode.h"
#include "ThresholdNode.h"
#include "EdgeDetectionNode.h"
#include "ConvolutionNode.h"
#include "NoiseNode.h"
#include "OutputNode.h"

NodeEditor::NodeEditor()
    : nextNodeId_(1)
    , nextLinkId_(1)
{}

void NodeEditor::Render() {
    // 1) UI to add nodes
    ImGui::Begin("Add Nodes");
    if (ImGui::Button("Add Input Node")) {
        inputNodes_.push_back(std::make_unique<ImageInputNode>(nextNodeId_++));
    }
    if (ImGui::Button("Add Brightness/Contrast")) {
        bcNodes_.push_back(std::make_unique<BrightnessContrastNode>(nextNodeId_++));
    }
    if (ImGui::Button("Add Channel Splitter")) {
        splitterNodes_.push_back(std::make_unique<ColorChannelSplitterNode>(nextNodeId_++));
    }
    if (ImGui::Button("Add Blur Node")) {
        blurNodes_.push_back(std::make_unique<BlurNode>(nextNodeId_++));
    }
    if (ImGui::Button("Add Threshold")) {
        thresholdNodes_.push_back(std::make_unique<ThresholdNode>(nextNodeId_++));
    }
    if (ImGui::Button("Add Edge Node")) {
        edgeNodes_.push_back(std::make_unique<EdgeDetectionNode>(nextNodeId_++));
    }
    if (ImGui::Button("Add Convolution Node")) {
        convNodes_.push_back(std::make_unique<ConvolutionNode>(nextNodeId_++));
    }
    if (ImGui::Button("Add Noise Node")) {
        noiseNodes_.push_back(std::make_unique<NoiseNode>(nextNodeId_++));
    }
    if (ImGui::Button("Add Output Node")) {
        outputNodes_.push_back(std::make_unique<OutputNode>(nextNodeId_++));
    }
    ImGui::End();

    // 2) Canvas
    ImNodes::BeginNodeEditor();
    for (auto& n : inputNodes_)      n->Render();
    for (auto& n : bcNodes_)         n->Render();
    for (auto& n : splitterNodes_)   n->Render();
    for (auto& n : blurNodes_)       n->Render();
    for (auto& n : thresholdNodes_)  n->Render();
    for (auto& n : edgeNodes_)       n->Render();
    for (auto& n : convNodes_)       n->Render();
    for (auto& n : noiseNodes_)      n->Render();
    for (auto& n : outputNodes_)     n->Render();
    for (auto& link : links_) {
        ImNodes::Link(link.id, link.start_attr, link.end_attr);
    }
    ImNodes::EndNodeEditor();

    // 3) New links
    int start_attr, end_attr;
    if (ImNodes::IsLinkCreated(&start_attr, &end_attr)) {
        links_.push_back({ nextLinkId_++, start_attr, end_attr });
        printf("Debug: Link created %d→%d\n", start_attr, end_attr);
    }

    // 4) Evaluate the graph
    EvaluateGraph();
}

void NodeEditor::EvaluateGraph() {
    std::map<int, cv::Mat> outputs;

    // 4.1) Seed with Input nodes
    for (auto& in : inputNodes_) {
        cv::Mat img = in->GetImage();
        if (!img.empty()) {
            outputs[in->GetId()] = img;
            printf("Debug: Eval seed Input %d size %dx%d\n",
                   in->GetId(), img.cols, img.rows);
        }
    }

    // 4.2) Seed with Noise nodes
    for (auto& noise : noiseNodes_) {
        cv::Mat img = noise->GetOutputImage();
        if (!img.empty()) {
            outputs[noise->GetId()] = img;
            printf("Debug: Eval seed Noise %d size %dx%d\n",
                   noise->GetId(), img.cols, img.rows);
        }
    }

    // 4.3) Propagate through all other nodes until stable
    bool progress = true;
    while (progress) {
        progress = false;

        for (auto& link : links_) {
            int s = link.start_attr / 10;
            int e = link.end_attr   / 10;
            auto it = outputs.find(s);
            if (it == outputs.end() || outputs.count(e)) continue;

            cv::Mat img = it->second;

            // Brightness/Contrast
            for (auto& bc : bcNodes_) {
                if (bc->GetId() == e) {
                    bc->SetInputImage(img);
                    outputs[e] = bc->GetOutputImage();
                    printf("Debug: Eval BC %d from %d\n", e, s);
                    progress = true;
                }
            }
            // Channel Splitter
            for (auto& splitter : splitterNodes_) {
                if (splitter->GetId() == e) {
                    splitter->SetInputImage(img);
                    printf("Debug: Eval Splitter %d from %d\n", e, s);
                    progress = true;
                }
                int attr = link.start_attr;
                int id   = attr / 10;
                int ch   = attr - id * 10 - 2;
                if (splitter->GetId() == id) {
                    outputs[e] = splitter->GetChannelImage(ch);
                    printf("Debug: Splitter %d ch %d → %d\n", id, ch, e);
                }
            }
            // Blur
            for (auto& blur : blurNodes_) {
                if (blur->GetId() == e) {
                    blur->SetInputImage(img);
                    outputs[e] = blur->GetOutputImage();
                    printf("Debug: Eval Blur %d from %d\n", e, s);
                    progress = true;
                }
            }
            // Threshold
            for (auto& th : thresholdNodes_) {
                if (th->GetId() == e) {
                    th->SetInputImage(img);
                    outputs[e] = th->GetOutputImage();
                    printf("Debug: Eval Threshold %d from %d\n", e, s);
                    progress = true;
                }
            }
            // Edge Detection
            for (auto& ed : edgeNodes_) {
                if (ed->GetId() == e) {
                    ed->SetInputImage(img);
                    outputs[e] = ed->GetOutputImage();
                    printf("Debug: Eval Edge %d from %d\n", e, s);
                    progress = true;
                }
            }
            // Convolution
            for (auto& conv : convNodes_) {
                if (conv->GetId() == e) {
                    conv->SetInputImage(img);
                    outputs[e] = conv->GetOutputImage();
                    printf("Debug: Eval Convolution %d from %d\n", e, s);
                    progress = true;
                }
            }
            // Output
            for (auto& out : outputNodes_) {
                if (out->GetId() == e) {
                    out->SetInputImage(img);
                    outputs[e] = img;
                    printf("Debug: Eval Output %d from %d\n", e, s);
                    progress = true;
                }
            }
        }
    }
}
