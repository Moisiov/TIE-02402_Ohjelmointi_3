#include "mapwindow.hh"
#include "handlers/gameeventhandler.hh"

#include <QApplication>


int main(int argc, char* argv[])
{

    QApplication app(argc, argv);

    std::shared_ptr<GameEventHandler> GEHandler = std::make_shared<GameEventHandler>();
    std::shared_ptr<ObjectManager> objManager = std::make_shared<ObjectManager>();

    MapWindow mapWindow (nullptr, GEHandler, objManager);
    mapWindow.show();
    return app.exec();
}
