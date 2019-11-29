#include <QtTest>

#include "handlers/gameeventhandler.hh"
#include "handlers/objectmanager.hh"

#include "core/worldgenerator.h"
#include "tiles/forest.h"
#include "tiles/grassland.h"
#include "tiles/swamp.hh"
#include "tiles/stone.hh"
#include "tiles/sand.hh"
#include "tiles/water.hh"

#include "exceptions/notenoughspace.h"
#include "exceptions/lackingresources.hh"
#include "exceptions/movementlimitation.hh"
#include "exceptions/invalidcoordinate.hh"
// add necessary includes here

class ObjectManagerTesting : public QObject
{
    Q_OBJECT

public:
    ObjectManagerTesting();
    ~ObjectManagerTesting() = default;

private slots:
    // Most of the functions are already tested through EventHandler testing
    void initTestCase();
    void checkTiles();
    void checkPlayerZone();
    void checkScouts();

private:
    std::shared_ptr<GameEventHandler> _GEHandler;
    std::shared_ptr<ObjectManager> _objM;
};

ObjectManagerTesting::ObjectManagerTesting():
    _GEHandler(nullptr),
    _objM(nullptr)
{

}

void ObjectManagerTesting::initTestCase()
{
    _GEHandler = std::make_shared<GameEventHandler>();
    _objM = std::make_shared<ObjectManager>();
    _GEHandler->setGEHandler(_GEHandler);
    _objM->setGEHandler(_GEHandler);
    _GEHandler->setObjectManager(_objM);
    _objM->setObjManager(_objM);

    unsigned map_x = 30;
    unsigned map_y = 30;

    _objM->setMapSize(map_x, map_y);

    Course::WorldGenerator::getInstance().addConstructor<Forest>(2);
    Course::WorldGenerator::getInstance().addConstructor<Grassland>(3);
    Course::WorldGenerator::getInstance().addConstructor<Sand>(1);
    Course::WorldGenerator::getInstance().addConstructor<Stone>(1);
    Course::WorldGenerator::getInstance().addConstructor<Swamp>(1);
    Course::WorldGenerator::getInstance().addConstructor<Water>(1);
    Course::WorldGenerator::getInstance().generateMap(map_x, map_y, 1, _objM, _GEHandler);

    std::vector<std::string> playerNames = {"Pelaaja 1", "Pelaaja 2"};
    std::vector<PlayerColor> colorList = {PlayerColor::BLUE, PlayerColor::RED};

    _GEHandler->initializeGame(playerNames, colorList, map_x, map_y);
}

void ObjectManagerTesting::checkTiles()
{
    Course::Coordinate invalidCoord1 (-1,-1);
    Course::Coordinate invalidCoord2 (31,31);
    Course::Coordinate headquartersCoord (3,15);
    Course::Coordinate workerCoord (3,14);

    std::vector<Course::Coordinate> coordList = {
        Course::Coordinate (0,0),
        Course::Coordinate (0,1),
        Course::Coordinate (0,2),
        Course::Coordinate (0,3),
        Course::Coordinate (0,4)
    };

    try {
        try {
            _objM->getTile(invalidCoord1);
        } catch (InvalidCoordinate e) {
            QVERIFY(e.msg() == "A negative value in coordinate!");
        }
        try {
            _objM->getTile(invalidCoord2);
        } catch (InvalidCoordinate e) {
            QVERIFY(e.msg() == "Given coordines are beyond map limits!");
            qDebug() << QString::fromStdString(e.msg());
        }

        std::shared_ptr<Course::TileBase> HQTile = _objM->getTile(headquartersCoord);
        QVERIFY(HQTile->getBuildings().size() == 1);
        QVERIFY(HQTile->getBuildings()[0]->getType() == "HeadQuarters");

        std::vector<std::shared_ptr<Course::WorkerBase>> workers = _objM->getUnitsOnCoord(workerCoord);
        QVERIFY(workers.size() == 1);
        QVERIFY(workers[0]->getType() == "Worker");

        std::vector<std::shared_ptr<Course::TileBase>> tiles = _objM->getTiles(coordList);
        QVERIFY(tiles.size() == 5);

    } catch (Course::BaseException e) {
        // Test failed
        qDebug() << QString::fromStdString(e.msg());
        QVERIFY(false);
    }
}

void ObjectManagerTesting::checkPlayerZone()
{
    std::shared_ptr<Player> player = _GEHandler->currentPlayer();
    std::vector<Course::Coordinate> zone = _objM->getPlayerZone(player);

    QVERIFY(zone.size() == 49);
}

void ObjectManagerTesting::checkScouts()
{
    std::shared_ptr<Player> player = _GEHandler->currentPlayer();
    std::vector<std::shared_ptr<UnitBase>> scouts = _objM->getPlayerScouts(player);

    QVERIFY(scouts.size() == 1);

    Course::Coordinate scoutLoc (3,16);
    QVERIFY(scouts[0]->getCoordinate() == scoutLoc);
}

QTEST_APPLESS_MAIN(ObjectManagerTesting)

#include "tst_objectmanagertesting.moc"
