#include "objectmanager.hh"
#include <QDebug>

ObjectManager::ObjectManager(unsigned map_x, unsigned map_y,
                             std::shared_ptr<Course::iGameEventHandler> gameEventHandler):
    _map_x(map_x),
    _map_y(map_y),
    _gameEventHandler(gameEventHandler)
{

}

void ObjectManager::setGEHandler(
        std::shared_ptr<Course::iGameEventHandler> gameEventHandler)
{
    _gameEventHandler = gameEventHandler;
}

void ObjectManager::setMapSize(unsigned map_x, unsigned map_y)
{
    _map_x = map_x;
    _map_y = map_y;
}


void ObjectManager::addTiles(const std::vector<std::shared_ptr<Course::TileBase> > &tiles)
{
    qDebug() << "In ObjectManager::addTiles()";

    _objects.insert(_objects.end(), tiles.begin(), tiles.end());

    for(int i = 0; i < static_cast<int>(_map_x); ++i) {
        std::vector<std::shared_ptr<Course::TileBase>> tilesTemp =
                std::vector<std::shared_ptr<Course::TileBase>>(tiles.begin() + i*static_cast<int>(_map_x),
                                                               tiles.begin() + (i+1)*static_cast<int>(_map_x)-1);
        _tiles.push_back(tilesTemp);
    }
}

std::shared_ptr<Course::TileBase> ObjectManager::getTile(const Course::Coordinate &coordinate)
{
    unsigned x = static_cast<unsigned>(coordinate.x());
    unsigned y = static_cast<unsigned>(coordinate.y());

    qDebug() << "X: " << x << ", Y: " << y;
    qDebug() << "_tiles.size() == " << _tiles.size();

    return _tiles.at(x).at(y);
}

std::shared_ptr<Course::TileBase> ObjectManager::getTile(const Course::ObjectId &id)
{
    std::shared_ptr<Course::TileBase> tile;

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

void ObjectManager::drawMap(std::shared_ptr<WorldScene> worldScene)
{
    for(unsigned i = 0; i < _objects.size(); ++i)
    {
        worldScene->drawItem(_objects.at(i));
    }
}

