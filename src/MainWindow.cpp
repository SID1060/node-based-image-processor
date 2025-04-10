#include "MainWindow.h"

#include <QGraphicsView>
#include <QDockWidget>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    m_canvasView = new QGraphicsView(this);
    setCentralWidget(m_canvasView);

    QWidget* propsWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(propsWidget);
    layout->addWidget(new QLabel("Node Properties Panel", propsWidget));

    m_propertiesDock = new QDockWidget("Properties", this);
    m_propertiesDock->setWidget(propsWidget);
    addDockWidget(Qt::RightDockWidgetArea, m_propertiesDock);

    setWindowTitle("Node‑Based Image Processor");
    resize(1200, 800);
}

MainWindow::~MainWindow() = default;
