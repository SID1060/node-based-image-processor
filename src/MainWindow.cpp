#include "MainWindow.h"
#include "NodeBox.h"
#include "ImageInputNode.h"
#include "BrightnessContrastNode.h"

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
#include <QSlider>

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

    // Add ImageInputNode
    m_addNodeAction = new QAction("New Node", this);
    addMenu->addAction(m_addNodeAction);

    // Add Brightness/Contrast Node
    QAction* addBCNode = new QAction("Brightness/Contrast Node", this);
    addMenu->addAction(addBCNode);

    // ImageInputNode spawn
    connect(m_addNodeAction, &QAction::triggered, this, [this]() {
        lastInputNode = new ImageInputNode();                    // store pointer to last image node
        ImageInputNode* newNode = lastInputNode;
        newNode->setPos(qrand() % 400, qrand() % 300);
        scene->addItem(newNode);
        connect(newNode, &NodeBox::nodeSelected, this, &MainWindow::onNodeSelected);
    });

    // Brightness/Contrast Node spawn
    connect(addBCNode, &QAction::triggered, this, [this]() {
        BrightnessContrastNode* bcNode = new BrightnessContrastNode();
        bcNode->setPos(qrand() % 400, qrand() % 300);

        // ✅ pass image from input node to brightness node
        if (lastInputNode)
            bcNode->setInputImage(lastInputNode->getImage());

        scene->addItem(bcNode);
        connect(bcNode, &NodeBox::nodeSelected, this, &MainWindow::onNodeSelected);
    });

    setWindowTitle("Node-Based Image Processor");
    resize(1200, 800);
}

void MainWindow::onNodeSelected(NodeBox* node) {
    QWidget* propsWidget = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(propsWidget);

    // IMAGE INPUT NODE
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
    }

    // BRIGHTNESS/CONTRAST NODE
    else if (auto* bcNode = dynamic_cast<BrightnessContrastNode*>(node)) {
        layout->addWidget(new QLabel("Brightness (-100 to 100)", propsWidget));
        QSlider* brightSlider = new QSlider(Qt::Horizontal, propsWidget);
        brightSlider->setRange(-100, 100);
        brightSlider->setValue(0);
        layout->addWidget(brightSlider);

        QPushButton* resetB = new QPushButton("Reset Brightness", propsWidget);
        layout->addWidget(resetB);

        layout->addWidget(new QLabel("Contrast (0.0 to 3.0)", propsWidget));
        QSlider* contrastSlider = new QSlider(Qt::Horizontal, propsWidget);
        contrastSlider->setRange(0, 300);  // 0.0 to 3.0
        contrastSlider->setValue(100);     // default = 1.0
        layout->addWidget(contrastSlider);

        QPushButton* resetC = new QPushButton("Reset Contrast", propsWidget);
        layout->addWidget(resetC);

        connect(brightSlider, &QSlider::valueChanged, bcNode, &BrightnessContrastNode::setBrightness);
        connect(contrastSlider, &QSlider::valueChanged, this, [bcNode](int val) {
            bcNode->setContrast(val / 100.0);
        });

        connect(resetB, &QPushButton::clicked, this, [brightSlider]() {
            brightSlider->setValue(0);
        });

        connect(resetC, &QPushButton::clicked, this, [contrastSlider]() {
            contrastSlider->setValue(100);
        });
    }

    // Default
    else {
        layout->addWidget(new QLabel("Selected: Node", propsWidget));
    }

    m_propertiesDock->setWidget(propsWidget);
}

MainWindow::~MainWindow() = default;
