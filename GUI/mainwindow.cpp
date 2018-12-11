#include "mainwindow.h"

#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_heatEquationSolver = new HeatEquationSolver("test.txt");
    m_openGLWidget = new OpenGLWidget(m_heatEquationSolver, this);
    setCentralWidget(m_openGLWidget);
}

MainWindow::~MainWindow()
{
    delete m_openGLWidget;
    delete m_heatEquationSolver;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_F) {
        m_openGLWidget->fitToScreen();
    }
    if (event->key() == Qt::Key_O){
        m_openGLWidget->toggleOverlay();
    }
}
