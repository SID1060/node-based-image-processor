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
#include "NodeEditor.h"
#include <imgui.h>
#include <imnodes.h>
#include <stdio.h>

NodeEditor::NodeEditor()
    : nextNodeId_(1)
    , nextLinkId_(1)
{}

void NodeEditor::Render() {
    // --- UI to add nodes ---
    ImGui::Begin("Add Nodes");
    if (ImGui::Button("Add Input Node")) {
        inputNodes_.push_back(std::make_unique<ImageInputNode>(nextNodeId_++));
    }
    if (ImGui::Button("Add Output Node")) {
        outputNodes_.push_back(std::make_unique<OutputNode>(nextNodeId_++));
    }
    ImGui::End();

    // --- Node editor canvas ---
    ImNodes::BeginNodeEditor();

    // 1) Render all nodes
    for (auto& in : inputNodes_)   in->Render();
    for (auto& out : outputNodes_) out->Render();

    // 2) Render existing links
    for (auto& link : links_) {
        ImNodes::Link(link.id, link.start_attr, link.end_attr);
    }

    ImNodes::EndNodeEditor();

    // --- Now, outside the editor scope, handle new links ---
    int start_attr, end_attr;
    if (ImNodes::IsLinkCreated(&start_attr, &end_attr)) {
        links_.push_back({ nextLinkId_++, start_attr, end_attr });
        printf("Debug: Link created from %d to %d\n", start_attr, end_attr);
    }
}
