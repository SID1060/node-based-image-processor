#ifndef NODE_EDITOR_H
#define NODE_EDITOR_H
#include "Nodes.h"
#include <vector>
#include <memory>

class NodeEditor {
public:
    NodeEditor();
    void Render();
private:
    std::vector<std::unique_ptr<ImageInputNode>> inputNodes_;
};

#endif

