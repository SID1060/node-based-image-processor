#include "Nodes.h"
#include <imgui.h>
#include <imnodes.h>
#include <imnodes_internal.h> // For GImNodes
#include <stdio.h> // For printf

void ImageInputNode::Render() {
    printf("Debug: Entering ImageInputNode::Render, Scope: %d\n", GImNodes ? GImNodes->CurrentScope : -1);
    ImNodes::BeginNode(id_);
    printf("Debug: After BeginNode, Scope: %d\n", GImNodes ? GImNodes->CurrentScope : -1);
    ImNodes::BeginNodeTitleBar();
    ImGui::Text("Image Input");
    ImNodes::EndNodeTitleBar();
    ImNodes::BeginOutputAttribute(id_ * 10 + 1);
    ImGui::Text("Image");
    ImNodes::EndOutputAttribute();
    ImNodes::EndNode();
    printf("Debug: Leaving ImageInputNode::Render, Scope: %d\n", GImNodes ? GImNodes->CurrentScope : -1);
}
