#include "startdialog.hh"
#include "mapwindow.hh"
#include "handlers/gameeventhandler.hh"
#include "handlers/objectmanager.hh"

#include <QApplication>


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    std::shared_ptr<GameEventHandler> GEHandler = std::make_shared<GameEventHandler>();
    std::shared_ptr<ObjectManager> objManager = std::make_shared<ObjectManager>(0,0, GEHandler);
    GEHandler->setObjectManager(objManager);

    MapWindow mapWindow (nullptr, GEHandler, objManager);

    if (mapWindow.isReadyToLaunch()) {
         mapWindow.show();
         return app.exec();
    } else {
        return EXIT_SUCCESS;
    }
}
