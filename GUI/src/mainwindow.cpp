#include "mainwindow.h"

#include <heatequationsolver.h>
#include <parser.h>
#include "openglwidget.h"
#include <QKeyEvent>
#include <QOpenGLWidget>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(HeatEquationSolver *solver, QWidget *parent)
    : QMainWindow(parent)
    , m_heatEquationSolver(solver),
      m_openGLWidget(nullptr)
{
    if (solver->valid()) {
        m_openGLWidget = new OpenGLWidget(m_heatEquationSolver, this);
        setCentralWidget(m_openGLWidget);
    } else {
        QMessageBox::warning(this, "Внимание", "Система несовместна");
    }

    m_menuBar = new QMenuBar(this);
    m_menu = m_menuBar->addMenu(tr("&Файл"));
    setMenuBar(m_menuBar);

    m_actionOpen = new QAction("Открыть файл", this);
    m_actionClose = new QAction("Выход", this);

    connect(m_actionOpen, SIGNAL(triggered()), this, SLOT(on_loadNewData()));
    connect(m_actionClose, SIGNAL(triggered()), this, SLOT(close()));
   // m_menu->addSeparator();
    m_menu->addAction(m_actionOpen);
    m_menu->addAction(m_actionClose);
}

MainWindow::~MainWindow()
{
    delete m_heatEquationSolver;
    delete m_openGLWidget;
    delete m_menu;
    delete m_menuBar;
    delete m_actionOpen;
    delete m_actionClose;
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

void MainWindow::on_loadNewData()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open data"), "", tr("Heat data loader (*.txt);;All Files (*.*)"));
    if (filename.isEmpty()){
        return;
    }

    const InputData data = parseFile(filename.toStdString());
    if (m_openGLWidget)
        delete m_openGLWidget;
    if (m_openGLWidget)
        delete m_heatEquationSolver;
    m_heatEquationSolver = new HeatEquationSolver(data);
    if (m_heatEquationSolver->valid()) {
        m_openGLWidget = new OpenGLWidget(m_heatEquationSolver, this);
        setCentralWidget(m_openGLWidget);
    } else {
        QMessageBox::warning(this, "Внимание", "Система несовместна");
    }
}
