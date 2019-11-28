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


// add necessary includes here

class GameEventHandlerTesting : public QObject
{
    Q_OBJECT

public:
    GameEventHandlerTesting();
    ~GameEventHandlerTesting() = default;

private slots:
    void initTestCase();
    void test_case1();

private:
    std::shared_ptr<GameEventHandler> _GEHandler;
    std::shared_ptr<ObjectManager> _objM;
};

GameEventHandlerTesting::GameEventHandlerTesting():
    _GEHandler(nullptr),
    _objM(nullptr)
{

}

void GameEventHandlerTesting::initTestCase()
{
    _GEHandler = std::make_shared<GameEventHandler>();
    _objM = std::make_shared<ObjectManager>();
    _GEHandler->setGEHandler(_GEHandler);
    _objM->setGEHandler(_GEHandler);
    _GEHandler->setObjectManager(_objM);
    _objM->setObjManager(_objM);

    unsigned map_x = 30;
    unsigned map_y = 30;

    Course::WorldGenerator::getInstance().addConstructor<Forest>(2);
    Course::WorldGenerator::getInstance().addConstructor<Grassland>(3);
    Course::WorldGenerator::getInstance().addConstructor<Sand>(1);
    Course::WorldGenerator::getInstance().addConstructor<Stone>(1);
    Course::WorldGenerator::getInstance().addConstructor<Swamp>(1);
    Course::WorldGenerator::getInstance().addConstructor<Water>(1);
    Course::WorldGenerator::getInstance().generateMap(map_x, map_y, 1, _objM, _GEHandler);

    _objM->drawMap();

    /*
    _GEHandler->initializeGame(playerList, colorList, map_x, map_y);
    _currentPlayer = m_GEHandler->currentPlayer();
    updatePlayerInfo();
    scrollToCoordinate(m_currentPlayer->getHQCoord());
    */
}

void GameEventHandlerTesting::test_case1()
{

}

QTEST_APPLESS_MAIN(GameEventHandlerTesting)

#include "tst_gameeventhandlertesting.moc"
