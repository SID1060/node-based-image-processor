#ifndef NODE_EDITOR_H
#define NODE_EDITOR_H

#include "Nodes.h"                       // ImageInputNode
#include "OutputNode.h"
#include "BrightnessContrastNode.h"
#include "ColorChannelSplitterNode.h"
#include "BlurNode.h"                   
#include "ThresholdNode.h"
#include "EdgeDetectionNode.h"
#include "ConvolutionNode.h"
#include "NoiseNode.h"
#include "BlendNode.h"
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
    std::vector<std::unique_ptr<BrightnessContrastNode>> bcNodes_;
    std::vector<std::unique_ptr<BlurNode>> blurNodes_;                    // <-- Add this line
    std::vector<std::unique_ptr<OutputNode>> outputNodes_;
    std::vector<std::unique_ptr<ColorChannelSplitterNode>> splitterNodes_;
    std::vector<std::unique_ptr<ThresholdNode>> thresholdNodes_;
    std::vector<std::unique_ptr<EdgeDetectionNode>>       edgeNodes_;
    std::vector<std::unique_ptr<ConvolutionNode>> convNodes_;
    std::vector<std::unique_ptr<NoiseNode>>       noiseNodes_;
    std::vector<std::unique_ptr<BlendNode>>       blendNodes_;
    std::vector<Link> links_;

    void EvaluateGraph();
};

#endif // NODE_EDITOR_H
