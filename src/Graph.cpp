#include "Graph.h"
#include <stdexcept>

void Graph::addNode(const NodePtr& node) {
    m_nodes.push_back(node);
    m_adj[node.get()];  // ensure entry exists
}

void Graph::connect(const NodePtr& from, const NodePtr& to) {
    // Link nodes
    to->addInput(from);
    m_adj[from.get()].push_back(to.get());

    // Check for cycles
    if (hasCycle()) {
        // Roll back
        m_adj[from.get()].pop_back();
        throw std::runtime_error("Graph connection would create a cycle");
    }
}

bool Graph::hasCycleUtil(Node* node, std::unordered_set<Node*>& visited, std::unordered_set<Node*>& recStack) {
    visited.insert(node);
    recStack.insert(node);

    for (auto* neigh : m_adj[node]) {
        if (!visited.count(neigh) && hasCycleUtil(neigh, visited, recStack))
            return true;
        if (recStack.count(neigh))
            return true;
    }

    recStack.erase(node);
    return false;
}

bool Graph::hasCycle() {
    std::unordered_set<Node*> visited, recStack;
    for (auto& n : m_nodes) {
        Node* ptr = n.get();
        if (!visited.count(ptr) && hasCycleUtil(ptr, visited, recStack))
            return true;
    }
    return false;
}

void Graph::topoSortUtil(Node* node, std::unordered_set<Node*>& visited, std::vector<Node*>& stack) {
    visited.insert(node);
    for (auto* neigh : m_adj[node]) {
        if (!visited.count(neigh))
            topoSortUtil(neigh, visited, stack);
    }
    stack.push_back(node);
}

std::vector<Node::Ptr> Graph::executionOrder() {
    if (hasCycle())
        throw std::runtime_error("Cannot get execution order: graph has cycles");

    std::unordered_set<Node*> visited;
    std::vector<Node*> stack;

    for (auto& n : m_nodes) {
        Node* ptr = n.get();
        if (!visited.count(ptr))
            topoSortUtil(ptr, visited, stack);
    }

    // Reverse stack to get correct order
    std::vector<NodePtr> order;
    for (auto it = stack.rbegin(); it != stack.rend(); ++it) {
        for (auto& sp : m_nodes) {
            if (sp.get() == *it) {
                order.push_back(sp);
                break;
            }
        }
    }
    return order;
}
