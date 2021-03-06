#include "scout.hh"

Scout::Scout(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
             const std::shared_ptr<Course::iObjectManager> &objectmanager,
             const std::shared_ptr<Course::PlayerBase> &owner,
             const int &tilespaces,
             const Course::ResourceMap &cost,
             const Course::ResourceMapDouble &efficiency,
             unsigned movementMax):
    UnitBase(eventhandler, objectmanager, owner, tilespaces, cost, efficiency, movementMax)
{

}

std::string Scout::getType() const
{
    return "Scout";
}
