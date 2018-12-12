#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "openglwidget.h"
#include "heatequationsolver.h"

#include <QMainWindow>
#include <QOpenGLWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    HeatEquationSolver *m_heatEquationSolver;
    OpenGLWidget *m_openGLWidget;
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // MAINWINDOW_H
