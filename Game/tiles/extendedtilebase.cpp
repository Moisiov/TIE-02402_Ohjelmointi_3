#include "extendedtilebase.h"
#include "player.hh"

ExtendedTileBase::ExtendedTileBase(const Course::Coordinate& location,
                   const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
                   const std::shared_ptr<Course::iObjectManager>& objectmanager,
                   const unsigned int& max_build,
                   const unsigned int& max_work,
                   const Course::ResourceMap& production,
                   const std::vector<std::string>& buildableBuildings):
    Course::TileBase(location, eventhandler, objectmanager, max_build, max_work, production),
    _buildableBuildings(buildableBuildings)
{
}

std::vector<std::string> ExtendedTileBase::getBuildableBuildings()
{
    return _buildableBuildings;
}

std::string ExtendedTileBase::description()
{
    std::string description = "";
    std::shared_ptr<Course::PlayerBase> owner = getOwner();

    if (owner != nullptr) {
        description += owner->getName() + "'s ";
    }

    description += getType() + " tile";

    return description;
}
