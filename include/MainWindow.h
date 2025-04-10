#pragma once

#include <QMainWindow>
class QGraphicsView;
class QDockWidget;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    QGraphicsView* m_canvasView;
    QDockWidget*  m_propertiesDock;
};
