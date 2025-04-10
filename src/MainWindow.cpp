#include "MainWindow.h"
#include "MainWindow.h"
#include "NodeBox.h"
#include "ImageInputNode.h"

#include <QMenuBar>
#include <QMenu>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDockWidget>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QAction>
#include <QPushButton>
#include <QFileDialog>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    // Create scene
    scene = new QGraphicsScene(this);
    
    // Create view
    m_canvasView = new QGraphicsView(scene, this);
    setCentralWidget(m_canvasView);

    // Create Properties panel
    QWidget* propsWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(propsWidget);
    layout->addWidget(new QLabel("Node Properties Panel", propsWidget));

    m_propertiesDock = new QDockWidget("Properties", this);
    m_propertiesDock->setWidget(propsWidget);
    addDockWidget(Qt::RightDockWidgetArea, m_propertiesDock);

    // Menu bar
    QMenu* addMenu = menuBar()->addMenu("Add");
    m_addNodeAction = new QAction("New Node", this);
    addMenu->addAction(m_addNodeAction);

    // Connect action to create ImageInputNode
    connect(m_addNodeAction, &QAction::triggered, this, [this]() {
        ImageInputNode* newNode = new ImageInputNode();
        newNode->setPos(qrand() % 400, qrand() % 300); // random position
        scene->addItem(newNode);
        connect(newNode, &NodeBox::nodeSelected, this, &MainWindow::onNodeSelected);
    });

    setWindowTitle("Node-Based Image Processor");
    resize(1200, 800);
}

void MainWindow::onNodeSelected(NodeBox* node) {
    QWidget* propsWidget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(propsWidget);

    if (auto* imgNode = dynamic_cast<ImageInputNode*>(node)) {
        QLabel* metaLabel = new QLabel("No image loaded", propsWidget);
        QPushButton* loadBtn = new QPushButton("Load Image", propsWidget);

        layout->addWidget(loadBtn);
        layout->addWidget(metaLabel);

        connect(loadBtn, &QPushButton::clicked, this, [imgNode, metaLabel]() {
            QString file = QFileDialog::getOpenFileName(nullptr, "Select Image", "", "Images (*.png *.jpg *.bmp)");
            if (!file.isEmpty()) {
                imgNode->setImage(file);
                metaLabel->setText(imgNode->getMetadata());
            }
        });
    } else {
        layout->addWidget(new QLabel("Selected: Node", propsWidget));
    }

    m_propertiesDock->setWidget(propsWidget);
}

MainWindow::~MainWindow() = default;

