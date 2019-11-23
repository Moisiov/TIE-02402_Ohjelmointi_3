#include "extendedtilebase.h"
#include "player.hh"
#include <QDebug>



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

bool ExtendedTileBase::generateResources()
{
    std::vector<std::shared_ptr<Course::BuildingBase>> buildings = getBuildings();
    std::vector<std::shared_ptr<Course::WorkerBase>> workers = getWorkers();

    Course::ResourceMap base = BASE_PRODUCTION;

    for (unsigned i = 0; i < buildings.size(); ++i)
    {
       Course::ResourceMap buildingProduction = buildings[i]->getProduction();

        base = mergeResourceMaps(base, buildingProduction);
    }

    Course::ResourceMapDouble totalEfficiency = ZERO;
    for (unsigned i = 0; i < workers.size(); ++i) {
        std::shared_ptr<UnitBase> unit = std::dynamic_pointer_cast<UnitBase>(workers[i]);
        Course::ResourceMapDouble workerEfficiency = unit->getEfficiency();
        totalEfficiency = Course::mergeResourceMapDoubles(totalEfficiency, workerEfficiency);
    }

    Course::ResourceMap totalProduction = fixedResourceMultiplier(base, totalEfficiency);

    return lockEventHandler()->modifyResources(getOwner(), totalProduction);
}
