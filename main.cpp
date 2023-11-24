#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include "sudoku.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    srand(time(NULL));
    Sudoku s{};
    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/QMLSudokuPuzzle/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed, &app, []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
    engine.load(url);
    
    return app.exec();
}
