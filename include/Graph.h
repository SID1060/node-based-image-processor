#pragma once
#include "Node.h"
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>

class Graph {
public:
    using NodePtr = Node::Ptr;

    // Add a node to the graph
    void addNode(const NodePtr& node);

    // Connect output of "from" into input of "to"
    // Throws if this would introduce a cycle
    void connect(const NodePtr& from, const NodePtr& to);

    // Returns nodes in topological (execution) order
    std::vector<NodePtr> executionOrder();

private:
    std::vector<NodePtr> m_nodes;
    std::unordered_map<Node*, std::vector<Node*>> m_adj;

    bool hasCycleUtil(Node* node, std::unordered_set<Node*>& visited, std::unordered_set<Node*>& recStack);
    bool hasCycle();
    void topoSortUtil(Node* node, std::unordered_set<Node*>& visited, std::vector<Node*>& stack);
};
