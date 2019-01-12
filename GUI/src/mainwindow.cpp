#include "mainwindow.h"

#include "openglwidget.h"
#include <heatequationsolver.h>
#include <QKeyEvent>
#include <QOpenGLWidget>

MainWindow::MainWindow(const HeatEquationSolver *solver, QWidget *parent)
    : QMainWindow(parent)
    , m_heatEquationSolver{solver}
{
    m_openGLWidget = new OpenGLWidget(m_heatEquationSolver, this);
    setCentralWidget(m_openGLWidget);
}

MainWindow::~MainWindow()
{
    delete m_openGLWidget;
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
