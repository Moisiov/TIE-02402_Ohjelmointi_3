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
    void turnHandling();

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

    std::shared_ptr<WorldScene> scene = std::make_shared<WorldScene>();
    _objM->setScene(scene);

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

    // _objM->drawMap();

    std::vector<std::string> playerNames = {"Pelaaja 1", "Pelaaja 2"};
    std::vector<PlayerColor> colorList = {PlayerColor::BLUE, PlayerColor::RED};

    _GEHandler->initializeGame(playerNames, colorList, map_x, map_y);

    std::shared_ptr<Player> player1 = _GEHandler->currentPlayer();
    QVERIFY(player1->getName() == "Pelaaja 1");
    QVERIFY(player1->getColor() == PlayerColor::BLUE);

    _GEHandler->endTurn();

    std::shared_ptr<Player> player2 = _GEHandler->currentPlayer();
    QVERIFY(player2->getName() == "Pelaaja 2");
    QVERIFY(player2->getColor() == PlayerColor::RED);
}

void GameEventHandlerTesting::turnHandling()
{
    QVERIFY(_GEHandler->currentTurn() == 1);
    _GEHandler->endTurn();
    QVERIFY(_GEHandler->currentTurn() == 0);

}

QTEST_APPLESS_MAIN(GameEventHandlerTesting)

#include "tst_gameeventhandlertesting.moc"
