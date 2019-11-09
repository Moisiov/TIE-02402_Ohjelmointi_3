#include "player.hh"

Player::Player(const std::string &name,
               PlayerColor color,
               const std::vector<std::shared_ptr<Course::GameObject> > objects):
    Course::PlayerBase(name, objects),
    _resources(PLAYER_STARTING_RESOURCES),
    _color(color),
    _ownedTiles({}),
    _ownedBuildings({}),
    _ownedUnits({})
{

}

Player::Player(const std::string &name,
               PlayerColor color,
               const Course::ResourceMap &startingResources,
               const std::vector<std::shared_ptr<Course::GameObject> > objects):
    Course::PlayerBase(name, objects), _resources(startingResources), _color(color)
{

}

void Player::addTile(std::shared_ptr<Course::TileBase> tile)
{
    _ownedTiles.push_back(tile);
}

void Player::addBuilding(std::shared_ptr<UpgradeableBuilding> building)
{
    _ownedBuildings.push_back(building);
}

void Player::addUnit(std::shared_ptr<UnitBase> unit)
{
    _ownedUnits.push_back(unit);
}

Course::ResourceMap Player::getResources()
{
    return _resources;
}

PlayerColor Player::getColor()
{
    return _color;
}

bool Player::canAfford(Course::ResourceMap cost)
{
    for (std::pair<Course::BasicResource, int> materialNeed : cost) {
        int materialOwned = _resources.at(materialNeed.first);
        if (materialOwned < materialNeed.second) {
            return false;
        }
    }

    return true;
}

bool Player::modifyResource(Course::BasicResource resource, int amount)
{
    _resources.at(resource) += amount;
    if (_resources.at(resource) < 0) {
        return false;
    } else {
        return true;
    }
}

bool Player::modifyResources(Course::ResourceMap resources)
{
    bool negativeResources = false;

    for (std::pair<Course::BasicResource, int> material : resources) {
        _resources.at(material.first) += material.second;
        if (_resources.at(material.first) < 0)
        {
            negativeResources = true;
        }
    }

    if (negativeResources) {
        return false;
    } else {
        return true;
    }
}
