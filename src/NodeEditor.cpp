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
#include "NodeEditor.h"
#include <imgui.h>
#include <imnodes.h>
#include <opencv2/opencv.hpp>
#include <map>
#include <cstdio>

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
    if (ImGui::Button("Add Output Node")) {
        outputNodes_.push_back(std::make_unique<OutputNode>(nextNodeId_++));
    }
    ImGui::End();

    // 2) Node editor canvas
    ImNodes::BeginNodeEditor();

    // Render all nodes
    for (auto& n : inputNodes_)  n->Render();
    for (auto& n : bcNodes_)     n->Render();
    for (auto& n : outputNodes_) n->Render();

    // Draw existing links
    for (auto& link : links_) {
        ImNodes::Link(link.id, link.start_attr, link.end_attr);
    }

    ImNodes::EndNodeEditor();

    // 3) Detect new links
    int start_attr, end_attr;
    if (ImNodes::IsLinkCreated(&start_attr, &end_attr)) {
        links_.push_back({ nextLinkId_++, start_attr, end_attr });
        printf("Debug: Link created %d→%d\n", start_attr, end_attr);
    }

    // 4) Propagate images through the graph
    EvaluateGraph();
}
void NodeEditor::EvaluateGraph() {
    std::map<int, cv::Mat> outputs;

    // 1) Seed with Input nodes
    for (auto& in : inputNodes_) {
        cv::Mat img = in->GetImage();
        if (!img.empty()) {
            outputs[in->GetId()] = img;
            printf("Debug: Eval seed Input %d size %dx%d\n",
                   in->GetId(), img.cols, img.rows);
        }
    }

    bool progress = true;
    while (progress) {
        progress = false;

        for (auto& link : links_) {
            int s = link.start_attr / 10;
            int e = link.end_attr   / 10;

            // Only proceed if we have an output for s, and haven't done e yet
            auto it = outputs.find(s);
            if (it == outputs.end() || outputs.count(e)) continue;

            cv::Mat img = it->second;

            // 2a) Brightness/Contrast nodes
            for (auto& bc : bcNodes_) {
                if (bc->GetId() == e) {
                    bc->SetInputImage(img);
                    outputs[e] = bc->GetOutputImage();
                    printf("Debug: Eval BC %d from %d\n", e, s);
                    progress = true;
                }
            }

            // 2b) Output nodes (terminal)
            for (auto& out : outputNodes_) {
                if (out->GetId() == e) {
                    out->SetInputImage(img);
                    // Mark as processed so we don't redo it endlessly
                    outputs[e] = img;
                    printf("Debug: Eval Output %d from %d\n", e, s);
                    progress = true;
                }
            }
        }
    }
}
