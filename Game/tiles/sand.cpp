#include "sand.hh"

Sand::Sand(const Course::Coordinate& location,
           const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
           const std::shared_ptr<Course::iObjectManager>& objectmanager,
           const unsigned int& max_build,
           const unsigned int& max_work,
           const Course::ResourceMap& production,
           const std::vector<std::string>& buildableBuildings):
    ExtendedTileBase(location,
                     eventhandler,
                     objectmanager,
                     max_build,
                     max_work,
                     production,
                     buildableBuildings){}

std::string Sand::getType() const
{
    return "Sand";
}
