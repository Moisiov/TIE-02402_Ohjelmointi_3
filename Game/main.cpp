#include "mapwindow.hh"
#include "handlers/gameeventhandler.hh"

#include <QApplication>


int main(int argc, char* argv[])
{

    QApplication app(argc, argv);

    std::shared_ptr<GameEventHandler> GEHandler = std::make_shared<GameEventHandler>();

    MapWindow mapWindow (nullptr, GEHandler);
    mapWindow.show();
    return app.exec();
}
