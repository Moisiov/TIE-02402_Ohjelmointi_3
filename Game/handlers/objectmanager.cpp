#include "objectmanager.hh"

ObjectManager::ObjectManager(int map_size,
                             std::shared_ptr<Course::iGameEventHandler> gameEventHandler):
    _gameEventHandler(gameEventHandler),
    _map_size(map_size)
{

}

void ObjectManager::setGEHandler(
        std::shared_ptr<Course::iGameEventHandler> gameEventHandler)
{
    _gameEventHandler = gameEventHandler;
}


void ObjectManager::addTiles(const std::vector<std::shared_ptr<Course::TileBase> > &tiles)
{
    _objects.insert(_objects.end(), tiles.begin(), tiles.end());

    for(int i = 0; i < _map_size; ++i) {
        std::vector<std::shared_ptr<Course::TileBase>> tilesTemp =
                std::vector<std::shared_ptr<Course::TileBase>>(tiles.begin() + i*_map_size,
                                                               tiles.begin() + (i+1)*_map_size-1);
        _tiles.push_back(tilesTemp);
    }
}

std::shared_ptr<Course::TileBase> ObjectManager::getTile(const Course::Coordinate &coordinate)
{
    int x = coordinate.x();
    int y = coordinate.y();

    return _tiles.at(x).at(y);
}

std::shared_ptr<Course::TileBase> ObjectManager::getTile(const Course::ObjectId &id)
{
    std::shared_ptr<Course::TileBase> tile;

    for(int x = 0; x < _map_size; ++x)
    {
        for(int y = 0; y < _map_size; ++y)
            if(_tiles.at(x).at(y)->ID == id)
            {
                tile = _tiles.at(x).at(y);
                break;
            }
    }

    return tile;
}

std::vector<std::shared_ptr<Course::TileBase> > ObjectManager::getTiles(const std::vector<Course::Coordinate> &coordinates)
{

}


