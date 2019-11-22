#include "objectmanager.hh"
#include <QDebug>

#include "buildings/hq.hh"
#include "buildings/ranch.hh"
#include "buildings/fishery.hh"
#include "buildings/sawmill.hh"
#include "buildings/mine.hh"
#include "buildings/market.hh"
#include "buildings/campus.hh"
#include "buildings/outpost.hh"

#include "workers/scout.hh"
#include "workers/worker.hh"

ObjectManager::ObjectManager(unsigned map_x, unsigned map_y,
                             std::shared_ptr<Course::iGameEventHandler> gameEventHandler,
                             std::shared_ptr<WorldScene> scene):
    _map_x(map_x),
    _map_y(map_y),
    _tiles({}),
    _buildings({}),
    _units({}),
    _gameEventHandler(gameEventHandler),
    _objectManager(nullptr),
    _scene(scene)
{

}

void ObjectManager::setGEHandler(
        std::shared_ptr<Course::iGameEventHandler> gameEventHandler)
{
    _gameEventHandler = gameEventHandler;
}

void ObjectManager::setObjManager(std::shared_ptr<ObjectManager> objectManager)
{
    _objectManager = objectManager;
}

void ObjectManager::setMapSize(unsigned map_x, unsigned map_y)
{
    _map_x = map_x;
    _map_y = map_y;
}

void ObjectManager::setScene(std::shared_ptr<WorldScene> scene)
{
    _scene = scene;
}


void ObjectManager::addTiles(const std::vector<std::shared_ptr<Course::TileBase> > &tiles)
{
    qDebug() << "In ObjectManager::addTiles()";

    for(int i = 0; i < static_cast<int>(_map_x); ++i) {
        std::vector<std::shared_ptr<Course::TileBase>> tilesTemp =
                std::vector<std::shared_ptr<Course::TileBase>>(tiles.begin() + i*static_cast<int>(_map_y),
                                                               tiles.begin() + (i+1)*static_cast<int>(_map_y));
        _tiles.push_back(tilesTemp);
    }
}

std::shared_ptr<Course::TileBase> ObjectManager::getTile(const Course::Coordinate &coordinate)
{
    unsigned x = static_cast<unsigned>(coordinate.x());
    unsigned y = static_cast<unsigned>(coordinate.y());

    return _tiles.at(x).at(y);
}

std::shared_ptr<Course::TileBase> ObjectManager::getTile(const Course::ObjectId &id)
{
    std::shared_ptr<Course::TileBase> tile = nullptr;

    for(unsigned x = 0; x < _map_x; ++x)
    {
        for(unsigned y = 0; y < _map_y; ++y)
            if(_tiles.at(x).at(y)->ID == id)
            {
                tile = _tiles.at(x).at(y);
                break;
            }
    }

    return tile;
}

std::vector<std::shared_ptr<Course::TileBase>> ObjectManager::getTiles(const std::vector<Course::Coordinate> &coordinates)
{
    std::vector<std::shared_ptr<Course::TileBase>> tiles;

    for(unsigned i = 0; i < coordinates.size(); ++i)
    {
        tiles.push_back(getTile(coordinates.at(i)));
    }

    return tiles;
}

void ObjectManager::constructBuilding(std::string type,
                                      Course::Coordinate location,
                                      std::shared_ptr<Player> owner)
{
    std::shared_ptr<UpgradeableBuilding> building = nullptr;

    if (type == "HeadQuarters") {
        building = std::make_shared<HQ>(_gameEventHandler, _objectManager, owner);
    } else if (type == "Outpost") {
        building= std::make_shared<Outpost>(_gameEventHandler, _objectManager, owner);
    } else if (type == "Farm") {
        building = std::make_shared<Ranch>(_gameEventHandler, _objectManager, owner);
    } else if (type == "Fishery") {
        building = std::make_shared<Fishery>(_gameEventHandler, _objectManager, owner);
    } else if (type == "Sawmill") {
        building = std::make_shared<Sawmill>(_gameEventHandler, _objectManager, owner);
    } else if (type == "Mine") {
        building = std::make_shared<Mine>(_gameEventHandler, _objectManager, owner);
    } else if (type == "Market") {
        building = std::make_shared<Market>(_gameEventHandler, _objectManager, owner);
    } else if (type == "Campus") {
        building = std::make_shared<Campus>(_gameEventHandler, _objectManager, owner);
    } else {
        qDebug() << "ObjectManager doesn't recoqnize building!";
        return;
    }

    building->setCoordinate(location);
    building->onBuildAction();
    getTile(location)->addBuilding(building);
    _buildings.push_back(building);
    drawItem(building);

    qDebug() << "Building " << building->ID << " built!";
}

void ObjectManager::addBuilding(const std::shared_ptr<UpgradeableBuilding> &building)
{
    _buildings.push_back(building);
}

bool ObjectManager::removeBuilding(Course::ObjectId ID)
{
    bool success = false;

    for (unsigned i = 0; i < _buildings.size(); ++i) {
        if (_buildings[i]->ID == ID) {
            _buildings.erase(_buildings.begin() + i);
            success = true;
            break;
        }
    }

    return success;
}

void ObjectManager::constructUnit(std::string type,
                                  Course::Coordinate location,
                                  std::shared_ptr<Player> owner)
{
    std::shared_ptr<UnitBase> unit = nullptr;

    if (type == "Scout") {
        unit = std::make_shared<Scout>(_gameEventHandler, _objectManager, owner);
    } else if (type == "Worker") {
        unit = std::make_shared<Worker>(_gameEventHandler, _objectManager, owner);
    } else {
        return;
    }

    unit->setCoordinate(location);
    getTile(location)->addWorker(unit);
    _units.push_back(unit);
    drawItem(unit);

    qDebug() << "Unit " << unit->ID << " built!";
}

void ObjectManager::addUnit(const std::shared_ptr<UnitBase> &unit)
{
    _units.push_back(unit);
}

void ObjectManager::drawMap()
{
    for(unsigned x = 0; x < _tiles.size(); ++x) {
        for(unsigned y = 0; y < _tiles.at(x).size(); ++y) {
            _scene->drawItem(_tiles.at(x).at(y));
        }
    }

    for(unsigned i = 0; i < _buildings.size(); ++i) {
        _scene->drawItem(_buildings.at(i));
    }

    for(unsigned i = 0; i < _units.size(); ++i) {
        _scene->drawItem(_units.at(i));
    }
}

void ObjectManager::drawItem(std::shared_ptr<Course::GameObject> obj)
{
    _scene->drawItem(obj);
}

void ObjectManager::restoreMoves(std::shared_ptr<Player> owner)
{
    std::string targetName = owner->getName();

    for (unsigned i = 0; i < _units.size(); ++i) {
        if (_units[i]->getOwner()->getName() == targetName) {
            _units[i]->rechargeMoves();
        }
    }
}

void ObjectManager::generateResources(std::shared_ptr<Player> owner)
{
    std::string targetName = owner->getName();

    for (unsigned x = 0; x < _tiles.size(); ++x) {
        for (unsigned y = 0; y < _tiles[x].size(); ++y) {
            std::shared_ptr<Course::PlayerBase> tileOwner = _tiles[x][y]->getOwner();
            if (tileOwner == nullptr) {
                continue;
            } else if (tileOwner->getName() == targetName) {
                _tiles[x][y]->generateResources();
            }
        }
    }
}

std::vector<std::shared_ptr<UnitBase> > ObjectManager::getPlayerScouts(std::shared_ptr<Player> player)
{
    std::vector<std::shared_ptr<UnitBase>> scoutList = {};

    for (unsigned i = 0; i < _units.size(); ++i) {
        std::shared_ptr<UnitBase> unit = _units[i];
        if (unit->getOwner()->getName() == player->getName()) {
            if (unit->getType() == "Scout") {
                scoutList.push_back(unit);
            }
        }
    }

    return scoutList;
}

