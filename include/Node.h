#pragma once
#include <string>
#include <vector>
#include <memory>
#include <opencv2/opencv.hpp>

class Node : public std::enable_shared_from_this<Node> {
public:
    using Ptr = std::shared_ptr<Node>;

    Node(const std::string& name);
    virtual ~Node();

    const std::string& name() const;

    void addInput(const Ptr& input);
    const std::vector<Ptr>& inputs() const;

    void markDirty();
    bool isDirty() const;

    // Compute this node's output
    cv::Mat getOutput();

    // Derived classes implement process
    virtual cv::Mat process() = 0;

protected:
    void onInputsChanged();

private:
    std::string m_name;
    std::vector<Ptr> m_inputs;
    std::vector<Ptr> m_outputs;
    bool m_dirty;
    cv::Mat m_cachedOutput;
};
