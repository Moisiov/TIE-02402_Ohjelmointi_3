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

// add necessary includes here

class GameEventHandlerTesting : public QObject
{
    Q_OBJECT

public:
    GameEventHandlerTesting();
    ~GameEventHandlerTesting() = default;

private slots:
    void initTestCase();
    void resourceManagement();
    void turnHandling();
    void buildUnits();
    void buildBuildings();
    void unitMovement();
    void buildOutpostOnScout();
    void upgradeUnits();
    void upgradeBuildings();
    void sellBuilding();

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

    std::shared_ptr<Player> player1 = _GEHandler->currentPlayer();
    QVERIFY(player1->getName() == "Pelaaja 1");
    QVERIFY(player1->getColor() == PlayerColor::BLUE);

    _GEHandler->endTurn();

    std::shared_ptr<Player> player2 = _GEHandler->currentPlayer();
    QVERIFY(player2->getName() == "Pelaaja 2");
    QVERIFY(player2->getColor() == PlayerColor::RED);
}

void GameEventHandlerTesting::resourceManagement()
{
    Course::ResourceMap startingResources = {
        {Course::BasicResource::NONE, 0},
        {Course::BasicResource::MONEY, 1000},
        {Course::BasicResource::FOOD, 600},
        {Course::BasicResource::WOOD, 400},
        {Course::BasicResource::STONE, 200},
        {Course::BasicResource::ORE, 0}
    };

    Course::ResourceMap resourceBonus = {
        {Course::BasicResource::NONE, 0},
        {Course::BasicResource::MONEY, 500},
        {Course::BasicResource::FOOD, 500},
        {Course::BasicResource::WOOD, 500},
        {Course::BasicResource::STONE, 500},
        {Course::BasicResource::ORE, 500}
    };

    Course::ResourceMap expectedResults = {
        {Course::BasicResource::NONE, 0},
        {Course::BasicResource::MONEY, 1500},
        {Course::BasicResource::FOOD, 1100},
        {Course::BasicResource::WOOD, 900},
        {Course::BasicResource::STONE, 700},
        {Course::BasicResource::ORE, 500}
    };

    std::shared_ptr<Player> player = _GEHandler->currentPlayer();
    Course::ResourceMap resources = player->getResources();
    QVERIFY(resources == startingResources);

    _GEHandler->modifyResources(player, resourceBonus);
    QVERIFY(player->getResources() == expectedResults);

    _GEHandler->modifyResource(player, Course::BasicResource::MONEY, -500);
    QVERIFY(player->getResources().at(Course::BasicResource::MONEY) == 1000);
}

void GameEventHandlerTesting::turnHandling()
{
    QVERIFY(_GEHandler->currentTurn() == 1);
    QVERIFY(_GEHandler->gameWon() == false);
    _GEHandler->endTurn();
    QVERIFY(_GEHandler->currentTurn() == 0);
    QVERIFY(_GEHandler->gameWon() == false);

}

void GameEventHandlerTesting::buildUnits()
{
    _GEHandler->constructUnit("Worker");
    _GEHandler->constructUnit("Worker");
    _GEHandler->constructUnit("Worker");
    try {
        _GEHandler->constructUnit("Worker");
    } catch (Course::NotEnoughSpace e) {
        QVERIFY(e.msg() == "Not enough space in HQ to build more units!");
    }
}

void GameEventHandlerTesting::buildBuildings()
{
    Course::Coordinate grassland (3,14);
    Course::Coordinate headquarters (3,15);
    Course::Coordinate farawayForest (8,15);
    Course::Coordinate freespot (2,15);

    try {
        try {
            _GEHandler->constructBuilding("Mine", grassland);
        } catch (Course::IllegalAction e) {
            QVERIFY(e.msg() == "Tile doesn't support given building type!");
        }

        QCOMPARE(true, _GEHandler->constructBuilding("Farm", grassland));

        try {
            _GEHandler->constructBuilding("Farm", grassland);
        } catch (Course::NotEnoughSpace e) {
            QVERIFY(e.msg() == "You can have only one building per tile!");
        }

        try {
            _GEHandler->constructBuilding("Sawmill", farawayForest);
        } catch (Course::IllegalAction e) {
            QVERIFY(e.msg() == "Players can only build on owned tiles or outposts on scout locations!");
        }
        try {
            _GEHandler->constructBuilding("Campus", freespot);
        } catch (LackingResources e) {
            QVERIFY(e.msg() == "Not enough resources to build Campus!");
        }

    } catch (Course::BaseException e) {
        // Test failed
        qDebug() << QString::fromStdString(e.msg());
        QVERIFY(false);
    }
}

void GameEventHandlerTesting::unitMovement()
{
    try {
        Course::Coordinate workerLoc (3,14);
        QVERIFY(_objM->getUnitsOnCoord(workerLoc).size() == 1);
        std::shared_ptr<UnitBase> worker = std::dynamic_pointer_cast<UnitBase>(_objM->getUnitsOnCoord(workerLoc)[0]);

        Course::Coordinate waterTile (4,13);
        try {
            _GEHandler->moveUnit(worker, waterTile);
        } catch (MovementLimitation e) {
            QVERIFY(e.msg() == "Worker cannot move on water!");
        }

        Course::Coordinate scoutLoc (3,16);
        QVERIFY(_objM->getUnitsOnCoord(scoutLoc).size() == 1);
        std::shared_ptr<UnitBase> scout = std::dynamic_pointer_cast<UnitBase>(_objM->getUnitsOnCoord(scoutLoc)[0]);

        Course::Coordinate headquarters (3,15);
        try {
            _GEHandler->moveUnit(scout, headquarters);
        } catch (Course::NotEnoughSpace e) {
            QVERIFY(e.msg() == "Destination already full of units!");
        }

        Course::Coordinate tooFar (3,25);
        try {
            _GEHandler->moveUnit(scout, tooFar);
        } catch (MovementLimitation e) {
            QVERIFY(e.msg() == "Unit cannot move that far!");
        }

        Course::Coordinate nearby (3,19);
        QCOMPARE(true, _GEHandler->moveUnit(scout, nearby));

        try {
            _GEHandler->moveUnit(scout, scoutLoc);
        } catch (MovementLimitation e) {
            QVERIFY(e.msg() == "Unit cannot move anymore this turn!");
        }

    } catch (Course::BaseException e) {
        // Test failed
        qDebug() << QString::fromStdString(e.msg());
        QVERIFY(false);
    }
}

void GameEventHandlerTesting::buildOutpostOnScout()
{
    Course::Coordinate scoutLoc (3,19);

    try {
        QVERIFY(_objM->getTile(scoutLoc)->getOwner() == nullptr);
        QCOMPARE(true, _GEHandler->constructBuilding("Outpost", scoutLoc));
        QVERIFY(_objM->getTile(scoutLoc)->getOwner() != nullptr);

    } catch (Course::BaseException e) {
        // Test failed
        qDebug() << QString::fromStdString(e.msg());
        QVERIFY(false);
    }
}

void GameEventHandlerTesting::upgradeUnits()
{
    try {
        Course::Coordinate workerLoc (3,14);
        QVERIFY(_objM->getUnitsOnCoord(workerLoc).size() == 1);
        std::shared_ptr<Worker> worker = std::dynamic_pointer_cast<Worker>(_objM->getUnitsOnCoord(workerLoc)[0]);

        QCOMPARE(true, _GEHandler->specializeUnit(worker, "Farmer"));

        try {
            _GEHandler->specializeUnit(worker, "Lumberjack");
        } catch (Course::IllegalAction e) {
            QVERIFY(e.msg() == "Unit cannot be specialized!");
        }

        Course::Coordinate headquarters (3,15);
        QVERIFY(_objM->getUnitsOnCoord(headquarters).size() == 3);
        std::shared_ptr<Worker> worker2 = std::dynamic_pointer_cast<Worker>(_objM->getUnitsOnCoord(headquarters)[0]);

        try {
            _GEHandler->specializeUnit(worker2, "Teekkari");
        } catch (LackingResources e) {
            QVERIFY(e.msg() == "Cannot afford to upgrade worker!");
        }

    } catch (Course::BaseException e) {
        // Test failed
        qDebug() << QString::fromStdString(e.msg());
        QVERIFY(false);
    }
}

void GameEventHandlerTesting::upgradeBuildings()
{
    try {
        Course::Coordinate headquartersLoc (3,15);
        std::shared_ptr<UpgradeableBuilding> headquarters =
                std::dynamic_pointer_cast<UpgradeableBuilding>(_objM->getTile(headquartersLoc)->getBuildings()[0]);
        try {
            _GEHandler->upgradeBuilding(headquarters);
        } catch (Course::IllegalAction e) {
            QVERIFY(e.msg() == "The building cannot be upgraded further!");
        }

        Course::Coordinate farmLoc (3,14);
        std::shared_ptr<UpgradeableBuilding> farm =
                std::dynamic_pointer_cast<UpgradeableBuilding>(_objM->getTile(farmLoc)->getBuildings()[0]);
        QCOMPARE(farm->getUpgradeTier(), 1);
        QCOMPARE(true, _GEHandler->upgradeBuilding(farm));
        QCOMPARE(farm->getUpgradeTier(), 2);

        try {
            _GEHandler->upgradeBuilding(farm);
        } catch (LackingResources e) {
            QVERIFY(e.msg() == "Not enough resources to upgrade Farm!");
        }

    } catch (Course::BaseException e) {
        // Test failed
        qDebug() << QString::fromStdString(e.msg());
        QVERIFY(false);
    }

}

void GameEventHandlerTesting::sellBuilding()
{
    Course::Coordinate outpostLoc (3,19);
    std::shared_ptr<Course::BuildingBase> outpost =
            _objM->getTile(outpostLoc)->getBuildings()[0];

    std::shared_ptr<Player> player = _GEHandler->currentPlayer();
    int prevWoodCount = player->getResources().at(Course::BasicResource::WOOD);

    _GEHandler->sellBuilding(outpost);

    int currentWoodCount = player->getResources().at(Course::BasicResource::WOOD);

    QVERIFY((prevWoodCount + 50) == currentWoodCount);
}

QTEST_APPLESS_MAIN(GameEventHandlerTesting)

#include "tst_gameeventhandlertesting.moc"
