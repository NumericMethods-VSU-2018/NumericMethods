#include "mainwindow.h"
#include <heatequationsolver.h>
#include <parser.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    const std::string filename = argc > 1 ? argv[1] : "test.txt";

    QStringList paths = QCoreApplication::libraryPaths();
    paths.append(".");
    paths.append("platforms");
    paths.append("plugins/platforms");

    QCoreApplication::setLibraryPaths(paths);
    QApplication a(argc, argv);

    const InputData data = parseFile(filename);
    const HeatEquationSolver solver(data);

    MainWindow w(&solver);
    w.show();

    return a.exec();
}
