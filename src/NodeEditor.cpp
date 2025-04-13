#include "NodeEditor.h"
#include <imgui.h>
#include <imnodes.h>
#include <stdio.h>

NodeEditor::NodeEditor() {
    printf("Debug: NodeEditor constructor called\n");
    inputNodes_.clear();
}

void NodeEditor::Render() {
    printf("Debug: Entering NodeEditor::Render\n");

    if (inputNodes_.empty()) {
        printf("Debug: Creating test node\n");
        inputNodes_.push_back(std::make_unique<ImageInputNode>(1));
    }

    for (auto& node : inputNodes_) {
        printf("Debug: Rendering node\n");
        node->Render();
        printf("Debug: Node rendered\n");
    }

    printf("Debug: Leaving NodeEditor::Render\n");
}
