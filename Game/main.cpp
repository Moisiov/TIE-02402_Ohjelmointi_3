#include "startdialog.hh"
#include "mapwindow.hh"
#include "handlers/gameeventhandler.hh"
#include "handlers/objectmanager.hh"
#include "exceptions/baseexception.h"

#include <QApplication>


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    std::shared_ptr<GameEventHandler> GEHandler = std::make_shared<GameEventHandler>();
    std::shared_ptr<ObjectManager> objManager = std::make_shared<ObjectManager>(0,0, GEHandler);
    GEHandler->setObjectManager(objManager);
    GEHandler->setGEHandler(GEHandler);
    objManager->setObjManager(objManager);

    std::shared_ptr<MapWindow> mapWindow = std::make_shared<MapWindow>(nullptr, GEHandler, objManager);

    if (!mapWindow->isReadyToLaunch()) {
        return EXIT_SUCCESS;
    }

    try {
        mapWindow->show();
        return app.exec();
    } catch (Course::BaseException e) {
        qDebug() << QString::fromStdString(e.msg());
        return EXIT_FAILURE;
    }
}
