#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class HeatEquationSolver;
class OpenGLWidget;

#include <QMainWindow>

class HeatEquationSolver;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(const HeatEquationSolver *solver, QWidget *parent = 0);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    const HeatEquationSolver *m_heatEquationSolver;
    OpenGLWidget *m_openGLWidget;
};

#endif // MAINWINDOW_H
