#pragma once

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDockWidget>
#include <QAction>

class NodeBox;
class ImageInputNode;             // forward declaration
class BrightnessContrastNode;     // forward declaration

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onNodeSelected(NodeBox* node);

private:
    QGraphicsScene* scene;
    QGraphicsView* m_canvasView;
    QDockWidget* m_propertiesDock;
    QAction* m_addNodeAction;

    // ✅ Added pointer to last ImageInputNode
    ImageInputNode* lastInputNode = nullptr;
};

