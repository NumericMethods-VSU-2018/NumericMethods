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
    MainWindow(HeatEquationSolver *solver, QWidget *parent = 0);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    QAction *m_actionOpen;
    QAction *m_actionClose;
    QMenuBar *m_menuBar;
    QMenu *m_menu;


    HeatEquationSolver *m_heatEquationSolver;
    OpenGLWidget *m_openGLWidget;

private slots:
    void on_loadNewData();
};

#endif // MAINWINDOW_H
