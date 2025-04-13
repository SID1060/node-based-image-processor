// #ifndef NODE_EDITOR_H
// #define NODE_EDITOR_H

// #include "Nodes.h"
// #include "OutputNode.h"
// // #include "BlendNode.h"
// #include <vector>
// #include <memory>
// #include <utility>

// struct Link {
//     int id;
//     int start_attr;
//     int end_attr;
// };

// class NodeEditor {
// public:
//     NodeEditor();
//     void Render();

// private:
//     int nextNodeId_;
//     int nextLinkId_;
//     std::vector<std::unique_ptr<ImageInputNode>> inputNodes_;
//     std::vector<std::unique_ptr<OutputNode>> outputNodes_;
//     // std::vector<std::unique_ptr<BlendNode>> blendNodes_;
//     std::vector<Link> links_;
// };

// #endif
#ifndef NODE_EDITOR_H
#define NODE_EDITOR_H

#include "Nodes.h"         // for ImageInputNode
#include "OutputNode.h"    // for OutputNode
#include <vector>
#include <memory>

struct Link {
    int id;
    int start_attr;
    int end_attr;
};

class NodeEditor {
public:
    NodeEditor();
    void Render();

private:
    int nextNodeId_;
    int nextLinkId_;
    std::vector<std::unique_ptr<ImageInputNode>> inputNodes_;
    std::vector<std::unique_ptr<OutputNode>> outputNodes_;
    std::vector<Link> links_;
};

#endif
