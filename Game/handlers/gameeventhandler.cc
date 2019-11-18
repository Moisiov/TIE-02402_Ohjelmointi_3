#include "gameeventhandler.hh"
#include "player.hh"
#include "buildings/hq.hh"
#include "workers/scout.hh"
#include "workers/worker.hh"
#include <math.h>

GameEventHandler::GameEventHandler():
    _objM(nullptr),
    _GEHandler(nullptr),
    _UI(nullptr),
    _playerList({}),
    _currentPlayer(0),
    _map_x(0),
    _map_y(0)
{

}

void GameEventHandler::setGEHandler(std::shared_ptr<GameEventHandler> GEHandler)
{
    _GEHandler = GEHandler;
}

void GameEventHandler::setObjectManager(std::shared_ptr<ObjectManager> objM)
{
    _objM = objM;
}

void GameEventHandler::setMapWindow(std::shared_ptr<MapWindow> UI)
{
    _UI = UI;
}

void GameEventHandler::initializeGame(std::vector<std::string> playerNames,
                                      std::vector<PlayerColor> playerColors,
                                      unsigned map_x, unsigned map_y)
{
    for (unsigned i = 0; i < playerNames.size(); ++i) {
        std::shared_ptr<Player> player = std::make_shared<Player>(playerNames[i], playerColors[i]);
        _playerList.push_back(player);
    }

    _map_x = map_x;
    _map_y = map_y;

    std::vector<Course::Coordinate> startPosition = {
        Course::Coordinate(0,0),
        Course::Coordinate(0,0),
        Course::Coordinate(0,0),
        Course::Coordinate(0,0),
        Course::Coordinate(0,0),
        Course::Coordinate(0,0)
    };

    int x_offset;
    if (map_x % 3 == 2) {
        x_offset = static_cast<int>((map_x - 14) / 3 + 1);
    } else {
        x_offset = static_cast<int>((map_x - 14) / 3);
    }

    // Player 1 coordinates
    startPosition[0].set_x(3);
    startPosition[0].set_y(static_cast<int>(map_y / 2));

    // Player 2 coordinates
    startPosition[1].set_x(static_cast<int>(map_x - 4));
    startPosition[1].set_y(static_cast<int>(map_y / 2));

    // Player 3 coordinates
    startPosition[2].set_x(x_offset + 3);
    startPosition[2].set_y(3);

    // Player 4 coordinates
    startPosition[3].set_x(static_cast<int>(map_x) - x_offset - 4);
    startPosition[3].set_y(static_cast<int>(map_y) - 4);

    // Player 5 coordinates
    startPosition[4].set_x(x_offset + 3);
    startPosition[4].set_y(static_cast<int>(map_y) - 4);

    // Player 6 coordinates
    startPosition[5].set_x(static_cast<int>(map_x) - x_offset - 4);
    startPosition[5].set_y(3);

    for (unsigned i = 0; i < _playerList.size(); ++i) {
        _playerList[i]->setHQCoord(startPosition[i]);
        _objM->getTile(startPosition[i])->setOwner(_playerList[i]);

        _objM->constructBuilding("HeadQuarters", startPosition[i], _playerList[i]);

        Course::Coordinate scoutCoord = startPosition[i] + Course::Coordinate(0,1);
        _objM->constructUnit("Scout", scoutCoord, _playerList[i]);

        Course::Coordinate workerCoord = startPosition[i] + Course::Coordinate(0,-1);
        _objM->constructUnit("Worker", workerCoord, _playerList[i]);

        qDebug() << QString::fromStdString(_playerList[i]->getName()) << "initialization success!";
    }
}

bool GameEventHandler::modifyResource(
        std::shared_ptr<Course::PlayerBase> player,
        Course::BasicResource resource,
        int amount)
{
    std::shared_ptr<Player> player_ptr = std::dynamic_pointer_cast<Player> (player);

    return player_ptr->modifyResource(resource, amount);
}

bool GameEventHandler::modifyResources(
        std::shared_ptr<Course::PlayerBase> player,
        Course::ResourceMap resources)
{
    std::shared_ptr<Player> player_ptr = std::dynamic_pointer_cast<Player> (player);

    return player_ptr->modifyResources(resources);
}

unsigned GameEventHandler::currentTurn()
{
    return _currentPlayer;
}

std::shared_ptr<Player> GameEventHandler::currentPlayer()
{
    return _playerList[_currentPlayer];
}

void GameEventHandler::endTurn()
{
    _currentPlayer += 1;
    if (_currentPlayer >= _playerList.size()) {
        _currentPlayer = 0;
    }

    _objM->restoreMoves(_playerList[_currentPlayer]);
    _objM->generateResources(_playerList[_currentPlayer]);
}

bool GameEventHandler::constructBuilding(std::string type, Course::Coordinate location)
{
    std::shared_ptr<Course::TileBase> targetTile = _objM->getTile(location);
    std::string tileType = targetTile->getType();

    bool tileSupportsBuildingType = false;

    // Checking if tile type can support buildings of given type
    if (tileType == "Forest") {
        for (unsigned i = 0; i < FOREST_BUILD.size(); ++i) {
            if (FOREST_BUILD[i] == type) {
                tileSupportsBuildingType = true;
            }
        }
    } else if (tileType == "Grassland") {
        for (unsigned i = 0; i < GRASSLAND_BUILD.size(); ++i) {
            if (GRASSLAND_BUILD[i] == type) {
                tileSupportsBuildingType = true;
            }
        }
    } else if (tileType == "Sand") {
        for (unsigned i = 0; i < SAND_BUILD.size(); ++i) {
            if (SAND_BUILD[i] == type) {
                tileSupportsBuildingType = true;
            }
        }
    } else if (tileType == "Stone") {
        for (unsigned i = 0; i < STONE_BUILD.size(); ++i) {
            if (STONE_BUILD[i] == type) {
                tileSupportsBuildingType = true;
            }
        }
    } else if (tileType == "Swamp") {
        for (unsigned i = 0; i < SWAMP_BUILD.size(); ++i) {
            if (SWAMP_BUILD[i] == type) {
                tileSupportsBuildingType = true;
            }
        }
    } else if (tileType == "Water") {
        for (unsigned i = 0; i < WATER_BUILD.size(); ++i) {
            if (WATER_BUILD[i] == type) {
                tileSupportsBuildingType = true;
            }
        }
    } else {
        qDebug() << "Tile type not recognized!";
        return false;
    }

    if (tileSupportsBuildingType == false) {
        qDebug() << "Tile doesn't support building type!";
        return false;
    }

    // Check if player can afford material cost
    Course::ResourceMap cost;
    if (type == "HeadQuarters") {
        cost = HQ_BUILD_COST_LIST[0];
    } else if (type == "Campus") {
        cost = CAMPUS_BUILD_COST_LIST[0];
    } else if (type == "Fishery") {
        cost = FISHERY_BUILD_COST_LIST[0];
    } else if (type == "Market") {
        cost = FISHERY_BUILD_COST_LIST[0];
    } else if (type == "Mine") {
        cost = MINE_BUILD_COST_LIST[0];
    } else if (type == "Ranch") {
        cost = RANCH_BUILD_COST_LIST[0];
    } else if (type == "Sawmill") {
        cost = SAWMILL_BUILD_COST_LIST[0];
    } else {
        qDebug() << "Building type not recoqnized!";
        return false;
    }

    if (not _playerList[_currentPlayer]->canAfford(cost)) {
        qDebug() << "Player cannot afford the building!";
        return false;
    }

    bool canBuild = false;

    // Checking if the player has a scout on an unowned tile
    std::vector<std::shared_ptr<UnitBase>> scoutList = _objM->getPlayerScouts(_playerList[_currentPlayer]);

    for (unsigned i = 0; i < scoutList.size(); ++i) {
        if (scoutList[i]->getCoordinate() == location) {
            if (targetTile->getOwner() == nullptr) {
                canBuild = true;
            }
        }
    }

    // Check if player owns the tile
    if (targetTile->getOwner() != nullptr) {
        if (targetTile->getOwner()->getName() == _playerList[_currentPlayer]->getName()) {
            canBuild = true;
        }
    }

    if (canBuild) {
        _objM->constructBuilding(type, location, _playerList[_currentPlayer]);
        Course::ResourceMap costNegative = Course::multiplyResourceMap(cost, NEGATIVE);
        _playerList[_currentPlayer]->modifyResources(costNegative);
        return true;
    } else {
        qDebug() << "The player cannot build on unowned land without a scout!";
        return false;
    }
}

bool GameEventHandler::upgradeBuilding(std::shared_ptr<Course::BuildingBase> building)
{
    std::shared_ptr<UpgradeableBuilding> upgrBuilding = std::static_pointer_cast<UpgradeableBuilding>(building);
    Course::ResourceMap cost = upgrBuilding->getUpgradeCost();

    if (not upgrBuilding->isUpgradeable()) {
        qDebug() << "Building cannot be upgraded any more!";
        return false;
    }

    if (not _playerList[_currentPlayer]->canAfford(cost)) {
        qDebug() << "Player can't afford the upgrade!";
        return false;
    }

    Course::ResourceMap costNegative = Course::multiplyResourceMap(cost, NEGATIVE);
    _playerList[_currentPlayer]->modifyResources(costNegative);

    upgrBuilding->upgradeBuilding();

    return true;
}

void GameEventHandler::sellBuilding(std::shared_ptr<Course::BuildingBase> building)
{
    std::shared_ptr<UpgradeableBuilding> upgrBuilding = std::static_pointer_cast<UpgradeableBuilding>(building);
    Course::ResourceMap sellValue = upgrBuilding->getSellValue();

    _objM->removeBuilding(upgrBuilding->ID);

    _playerList[_currentPlayer]->modifyResources(sellValue);

    return;
}

bool GameEventHandler::constructUnit(std::string type)
{
    // TODO!!
    return true;
}

bool GameEventHandler::moveUnit(std::shared_ptr<Course::WorkerBase> unit, Course::Coordinate destination)
{
    // TODO!!
    return true;
}
