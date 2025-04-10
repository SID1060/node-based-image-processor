#include "Node.h"

Node::Node(const std::string& name)
    : m_name(name), m_dirty(true) {}

Node::~Node() = default;

const std::string& Node::name() const { return m_name; }

void Node::addInput(const Ptr& input) {
    m_inputs.push_back(input);
    input->m_outputs.push_back(shared_from_this());
    markDirty();
}

const std::vector<Node::Ptr>& Node::inputs() const {
    return m_inputs;
}

void Node::markDirty() {
    if (!m_dirty) {
        m_dirty = true;
        for (auto& out : m_outputs) {
            out->markDirty();
        }
    }
}

bool Node::isDirty() const { return m_dirty; }

cv::Mat Node::getOutput() {
    if (m_dirty) {
        m_cachedOutput = process();
        m_dirty = false;
    }
    return m_cachedOutput;
}
