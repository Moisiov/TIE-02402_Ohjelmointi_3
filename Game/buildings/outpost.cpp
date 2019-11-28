#include "outpost.hh"
#include "tiles/tilebase.h"

Outpost::Outpost(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
       const std::shared_ptr<Course::iObjectManager> &objectmanager,
       const std::shared_ptr<Course::PlayerBase> &owner,
       const int &tilespaces,
       const std::vector<Course::ResourceMap> &buildcost,
       const std::vector<Course::ResourceMap> &production,
       const unsigned int maxTier):
    UpgradeableBuilding(eventhandler, objectmanager, owner, tilespaces, buildcost, production, maxTier)
{

}

std::string Outpost::getType() const
{
    return "Outpost";
}

void Outpost::onBuildAction()
{
    lockObjectManager()->getTile(getCoordinate())->setOwner(getOwner());

    std::vector< std::shared_ptr<Course::TileBase> > neighbours =
            lockObjectManager()->getTiles(getCoordinatePtr()->neighbours(1));

    for(auto it = neighbours.begin(); it != neighbours.end(); ++it)
    {
        // If the Tile doesn't have owner, set it's owner to buildings owner.
        if( not (*it)->getOwner() )
        {
            (*it)->setOwner(getOwner());
        }
    }
}
