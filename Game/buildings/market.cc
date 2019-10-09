#include "market.hh"

Market::Market(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
               const std::shared_ptr<Course::iObjectManager> &objectmanager,
               const std::shared_ptr<Course::PlayerBase> &owner,
               const int &tilespaces,
               const std::vector<Course::ResourceMap> &buildcost,
               const std::vector<Course::ResourceMap> &production,
               const unsigned int maxTier
               ):
    UpgradeableBuilding(eventhandler, objectmanager, owner, tilespaces, buildcost, production, maxTier)
{

}

std::string Market::getType() const
{
    return "Market";
}
