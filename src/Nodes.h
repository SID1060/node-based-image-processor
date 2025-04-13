// Nodes.h
#ifndef NODES_H
#define NODES_H
#include <opencv2/opencv.hpp>

class ImageInputNode {
public:
    ImageInputNode(int id) : id_(id) {}
    void Render();
    int GetId() const { return id_; }
private:
    int id_;
};

#endif