#include "gameeventhandler.hh"
#include "player.hh"
#include "buildings/hq.hh"
#include "workers/scout.hh"
#include "workers/worker.hh"
#include <math.h>

#include "exceptions/lackingresources.hh"
#include "exceptions/movementlimitation.hh"
#include "exceptions/notenoughspace.h"
#include "exceptions/ownerconflict.h"

GameEventHandler::GameEventHandler():
    _objM(nullptr),
    _GEHandler(nullptr),
    _playerList({}),
    _currentPlayer(0),
    _turn(1),
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
        _turn += 1;
    }

    _objM->restoreMoves(_playerList[_currentPlayer]);

    if (_turn > 1) {
        _objM->generateResources(_playerList[_currentPlayer]);
    }
}

bool GameEventHandler::gameWon()
{
    return _objM->progressResearch(_playerList[_currentPlayer]);
}

bool GameEventHandler::scoutOnUnownedTile(Course::Coordinate location)
{
    std::shared_ptr<Course::TileBase> targetTile = _objM->getTile(location);
    std::vector<std::shared_ptr<UnitBase>> scoutList = _objM->getPlayerScouts(_playerList[_currentPlayer]);

    bool hasScout = false;

    for (unsigned i = 0; i < scoutList.size(); ++i) {
        if (scoutList[i]->getCoordinate() == location) {
            if (targetTile->getOwner() == nullptr) {
                hasScout = true;
            }
        }
    }

    return hasScout;
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
        throw Course::BaseException("Tile type: " + tileType + " not recognized!");
    }



    if (tileSupportsBuildingType == false) {
        throw Course::IllegalAction("Tile doesn't support given building type!");
    }

    bool canBuild = false;



    // Check if player owns the tile
    if (targetTile->getOwner() != nullptr) {
        if (targetTile->getOwner()->getName() == _playerList[_currentPlayer]->getName()) {
            canBuild = true;
        }
    } else // Tile is unowned
    {
        if (scoutOnUnownedTile(location)) {
            if (type != "Outpost") {
                throw Course::IllegalAction("Only outposts can be built outside owned land!");
            } else {
                canBuild = true;
            }
        } else {
            throw Course::IllegalAction("Players can only build on owned tiles or outposts on scout locations!");
        }
    }

    if (!targetTile->hasSpaceForBuildings(1)) {
        throw Course::NotEnoughSpace("You can have only one building per tile!");
    }

   // Check if player can afford material cost
   Course::ResourceMap cost;
   if (type == "HeadQuarters") {
       cost = HQ_BUILD_COST_LIST[0];
   } else if (type == "Outpost") {
       cost = OUTPOST_BUILD_COST_LIST[0];
   } else if (type == "Campus") {
       cost = CAMPUS_BUILD_COST_LIST[0];
   } else if (type == "Fishery") {
       cost = FISHERY_BUILD_COST_LIST[0];
   } else if (type == "Market") {
       cost = FISHERY_BUILD_COST_LIST[0];
   } else if (type == "Mine") {
       cost = MINE_BUILD_COST_LIST[0];
   } else if (type == "Farm") {
       cost = RANCH_BUILD_COST_LIST[0];
   } else if (type == "Sawmill") {
       cost = SAWMILL_BUILD_COST_LIST[0];
   } else {
       throw Course::BaseException("Building type: " + type + " not recognized!");
   }

   if (not _playerList[_currentPlayer]->canAfford(cost)) {
       throw LackingResources("Not enough resources to build " + type + "!");
   }

    if (canBuild) {
        _objM->constructBuilding(type, location, _playerList[_currentPlayer]);
        _playerList[_currentPlayer]->payResourceCost(cost);
        return true;
    } else {
        return false;
    }
}

bool GameEventHandler::upgradeBuilding(std::shared_ptr<Course::BuildingBase> building)
{
    std::shared_ptr<UpgradeableBuilding> upgrBuilding = std::static_pointer_cast<UpgradeableBuilding>(building);
    Course::ResourceMap cost = upgrBuilding->getUpgradeCost();

    if (not upgrBuilding->isUpgradeable()) {
        throw Course::IllegalAction("The building cannot be upgraded further!");
    }

    if (not _playerList[_currentPlayer]->canAfford(cost)) {
        throw LackingResources("Not enough resources to upgrade " + building->getType() + "!");
    }

    _playerList[_currentPlayer]->payResourceCost(cost);

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
    Course::ResourceMap recruitCost = {};

    if (type == "Scout") {
        recruitCost = SCOUT_BUILD_COST;
    } else if (type == "Worker") {
        recruitCost = BASIC_WORKER_BUILD_COST;
    } else {
        throw Course::BaseException("Unit type: " + type + " not recognized!");
    }

    if (not _playerList[_currentPlayer]->canAfford(recruitCost)) {
        throw LackingResources("Not enough resources to recruit a " + type + "!");
    }

    Course::Coordinate buildLocation = _playerList[_currentPlayer]->getHQCoord();
    std::shared_ptr<Course::TileBase> buildTile = _objM->getTile(buildLocation);
    if (not buildTile->hasSpaceForWorkers(1)) {
        throw Course::NotEnoughSpace("Not enough space in HQ to build more units!");
    }

    _playerList[_currentPlayer]->payResourceCost(recruitCost);

    _objM->constructUnit(type, buildLocation, _playerList[_currentPlayer]);

    return true;
}

bool GameEventHandler::moveUnit(std::shared_ptr<UnitBase> unit, Course::Coordinate destination)
{
    if (not unit->canMove()) {
        throw MovementLimitation("Unit cannot move anymore this turn!");
    }

    bool canWalkOnWater = false;
    if (unit->getType() == "Scout") {
        canWalkOnWater = true;
    }

    int moveRange = static_cast<int>(unit->moveRange());
    Course::Coordinate distance = destination - unit->getCoordinate();

    int x_distance = (distance.x() >= 0 ? distance.x() : (distance.x() * -1));
    int y_distance = (distance.y() >= 0 ? distance.y() : (distance.y() * -1));

    if (x_distance > moveRange || y_distance > moveRange) {
        throw MovementLimitation("Unit cannot move that far!");
    }

    std::shared_ptr<Course::TileBase> originTile = _objM->getTile(unit->getCoordinate());
    std::shared_ptr<Course::TileBase> destinationTile = _objM->getTile(destination);

    if (destinationTile->getType() == "Water") {
        if (not canWalkOnWater) {
            if (destinationTile->getBuildingCount() < 1) {
                throw MovementLimitation("Worker cannot move on water!");
            }
            // Only Fisheries can exist on water tiles, and workers can move on them
        }
    }

    if (not destinationTile->hasSpaceForWorkers(1)) {
        throw Course::NotEnoughSpace("Destination already full of units!");
    }

    if (destinationTile->getOwner() != nullptr) {
        if (destinationTile->getOwner()->getName() != unit->getOwner()->getName()) {
            throw MovementLimitation("Units cannot move into enemy territory!");
        }
    } else {
        // DestinationTile not owned by anyone
        if (unit->getType() != "Scout") {
            throw MovementLimitation("Only scouts can go outside of players own lands!");
        }
    }

    // All good, do the move
    unit->setCoordinate(destination);
    originTile->removeWorker(unit);
    destinationTile->addWorker(unit);
    unit->wasMoved();

    return true;
}

bool GameEventHandler::specializeUnit(std::shared_ptr<Worker> unit, std::string specialization)
{
    if (unit->getType() != "Worker") {
        throw Course::IllegalAction("Unit cannot be specialized!");
    }

    if (SPECIALIZATION_COST.find(specialization) == SPECIALIZATION_COST.end()) {
        throw Course::BaseException("Cannot recognize specialization type: " + specialization + ".");
    }

    Course::ResourceMap cost = SPECIALIZATION_COST.find(specialization)->second;

    if (!_playerList[_currentPlayer]->canAfford(cost)) {
        throw LackingResources("Cannot afford to upgrade worker!");
    }

    // All good, do upgrade
    _playerList[_currentPlayer]->payResourceCost(cost);
    unit->specializeInto(specialization);

    return true;
}

std::vector<Course::Coordinate> GameEventHandler::getCurrentPlayerZone()
{
    return _objM->getPlayerZone(_playerList[_currentPlayer]);
}
