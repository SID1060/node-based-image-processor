#include "NodeEditor.h"
#include <imgui.h>
#include <imnodes.h>
#include <opencv2/opencv.hpp>
#include <map>
#include <cstdio>

// Include all custom nodes
#include "BrightnessContrastNode.h"
#include "ColorChannelSplitterNode.h"
#include "BlurNode.h"
#include "ThresholdNode.h"
#include "EdgeDetectionNode.h"
#include "ConvolutionNode.h"
#include "NoiseNode.h"
#include "BlendNode.h"
#include "OutputNode.h"

NodeEditor::NodeEditor()
    : nextNodeId_(1)
    , nextLinkId_(1)
{}

void NodeEditor::Render() {
    // 1) Node‑adding UI
    ImGui::Begin("Add Nodes");
    if (ImGui::Button("Add Input Node")) {
        inputNodes_.push_back(std::make_unique<ImageInputNode>(nextNodeId_++));
    }
    if (ImGui::Button("Add Brightness/Contrast")) {
        bcNodes_.push_back(std::make_unique<BrightnessContrastNode>(nextNodeId_++));
    }
    if (ImGui::Button("Add Channel Splitter")) {
        splitterNodes_.push_back(std::make_unique<ColorChannelSplitterNode>(nextNodeId_++));
    }
    if (ImGui::Button("Add Blur Node")) {
        blurNodes_.push_back(std::make_unique<BlurNode>(nextNodeId_++));
    }
    if (ImGui::Button("Add Threshold")) {
        thresholdNodes_.push_back(std::make_unique<ThresholdNode>(nextNodeId_++));
    }
    if (ImGui::Button("Add Edge Node")) {
        edgeNodes_.push_back(std::make_unique<EdgeDetectionNode>(nextNodeId_++));
    }
    if (ImGui::Button("Add Convolution Node")) {
        convNodes_.push_back(std::make_unique<ConvolutionNode>(nextNodeId_++));
    }
    if (ImGui::Button("Add Noise Node")) {
        noiseNodes_.push_back(std::make_unique<NoiseNode>(nextNodeId_++));
    }
    if (ImGui::Button("Add Blend Node")) {
        blendNodes_.push_back(std::make_unique<BlendNode>(nextNodeId_++));
    }
    if (ImGui::Button("Add Output Node")) {
        outputNodes_.push_back(std::make_unique<OutputNode>(nextNodeId_++));
    }
    ImGui::End();

    // 2) Canvas
    ImNodes::BeginNodeEditor();
    for (auto& n : inputNodes_)      n->Render();
    for (auto& n : bcNodes_)         n->Render();
    for (auto& n : splitterNodes_)   n->Render();
    for (auto& n : blurNodes_)       n->Render();
    for (auto& n : thresholdNodes_)  n->Render();
    for (auto& n : edgeNodes_)       n->Render();
    for (auto& n : convNodes_)       n->Render();
    for (auto& n : noiseNodes_)      n->Render();
    for (auto& n : blendNodes_)      n->Render();
    for (auto& n : outputNodes_)     n->Render();
    for (auto& link : links_) {
        ImNodes::Link(link.id, link.start_attr, link.end_attr);
    }
    ImNodes::EndNodeEditor();

    // 3) Capture new links
    int start_attr, end_attr;
    if (ImNodes::IsLinkCreated(&start_attr, &end_attr)) {
        links_.push_back({ nextLinkId_++, start_attr, end_attr });
        printf("Debug: Link created %d → %d\n", start_attr, end_attr);
    }

    // 4) Run the data‐flow
    EvaluateGraph();
}

void NodeEditor::EvaluateGraph() {
    std::map<int, cv::Mat> outputs;

    // 4.1) Seed inputs
    for (auto& in : inputNodes_) {
        cv::Mat img = in->GetImage();
        if (!img.empty()) {
            outputs[in->GetId()] = img;
            printf("Debug: Eval seed Input %d (size %dx%d)\n",
                   in->GetId(), img.cols, img.rows);
        }
    }
    // 4.2) Seed noise
    for (auto& noise : noiseNodes_) {
        cv::Mat img = noise->GetOutputImage();
        if (!img.empty()) {
            outputs[noise->GetId()] = img;
            printf("Debug: Eval seed Noise %d (size %dx%d)\n",
                   noise->GetId(), img.cols, img.rows);
        }
    }

    bool progress = true;
    while (progress) {
        progress = false;

        for (auto& link : links_) {
            int s = link.start_attr / 10;
            int e = link.end_attr   / 10;
            auto it = outputs.find(s);
            if (it == outputs.end() || outputs.count(e))
                continue;

            cv::Mat img = it->second;

            // — Brightness/Contrast —
            for (auto& bc : bcNodes_) {
                if (bc->GetId() == e) {
                    bc->SetInputImage(img);
                    outputs[e] = bc->GetOutputImage();
                    printf("Debug: Eval BC %d from %d\n", e, s);
                    progress = true;
                }
            }

            // — Channel Splitter (***fixed***) —
            {
                int endAttr      = link.end_attr;
                int splitterId   = endAttr / 10;
                int channelIndex = (endAttr % 10) - 2;

                for (auto& sp : splitterNodes_) {
                    if (sp->GetId() == splitterId) {
                        sp->SetInputImage(img);
                        outputs[e] = sp->GetChannelImage(channelIndex);
                        printf("Debug: Eval Splitter %d → channel %d from %d\n",
                               e, channelIndex, s);
                        progress = true;
                    }
                }
            }

            // — Blur —
            for (auto& bz : blurNodes_) {
                if (bz->GetId() == e) {
                    bz->SetInputImage(img);
                    outputs[e] = bz->GetOutputImage();
                    printf("Debug: Eval Blur %d from %d\n", e, s);
                    progress = true;
                }
            }

            // — Threshold —
            for (auto& th : thresholdNodes_) {
                if (th->GetId() == e) {
                    th->SetInputImage(img);
                    outputs[e] = th->GetOutputImage();
                    printf("Debug: Eval Threshold %d from %d\n", e, s);
                    progress = true;
                }
            }

            // — Edge Detection —
            for (auto& ed : edgeNodes_) {
                if (ed->GetId() == e) {
                    ed->SetInputImage(img);
                    outputs[e] = ed->GetOutputImage();
                    printf("Debug: Eval Edge %d from %d\n", e, s);
                    progress = true;
                }
            }

            // — Convolution —
            for (auto& cvn : convNodes_) {
                if (cvn->GetId() == e) {
                    cvn->SetInputImage(img);
                    outputs[e] = cvn->GetOutputImage();
                    printf("Debug: Eval Convolution %d from %d\n", e, s);
                    progress = true;
                }
            }

            // — Blend —
            for (auto& b : blendNodes_) {
                if (b->GetId() != e) continue;
                const int portA = e*10 + 1;
                const int portB = e*10 + 2;

                if (link.end_attr == portA) {
                    int src = link.start_attr/10;
                    b->SetInputImageA(outputs[src]);
                    printf("Debug: BlendNode %d got A from %d\n", e, src);
                    progress = true;
                }
                if (link.end_attr == portB) {
                    int src = link.start_attr/10;
                    b->SetInputImageB(outputs[src]);
                    printf("Debug: BlendNode %d got B from %d\n", e, src);
                    progress = true;
                }
                if (b->HasBothInputs()) {
                    outputs[e] = b->GetBlendedImage();
                    printf("Debug: Eval Blend %d → output\n", e);
                    progress = true;
                }
            }

            // — Output —
            for (auto& out : outputNodes_) {
                if (out->GetId() == e) {
                    printf("Debug: Setting OutputNode %d image (size %dx%d)\n",
                           e, img.cols, img.rows);
                    out->SetInputImage(img);
                    outputs[e] = img;
                    progress = true;
                }
            }
        }
    }
}
