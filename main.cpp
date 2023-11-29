#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include <QQmlContext>
#include "sudoku.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
       
    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/QMLSudokuPuzzle/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed, &app, []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
    
    Sudoku s{};
    QQmlContext* rootContext = engine.rootContext();
    rootContext->setContextProperty("sudokuModel", &s);
    engine.load(url);
    
    return app.exec();
}
