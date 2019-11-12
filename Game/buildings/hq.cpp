#include "hq.hh"
#include "tiles/tilebase.h"
#include <QDebug>

HQ::HQ(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
       const std::shared_ptr<Course::iObjectManager> &objectmanager,
       const std::shared_ptr<Course::PlayerBase> &owner,
       const int &tilespaces,
       const std::vector<Course::ResourceMap> &buildcost,
       const std::vector<Course::ResourceMap> &production,
       const unsigned int maxTier):
    UpgradeableBuilding(eventhandler, objectmanager, owner, tilespaces, buildcost, production, maxTier)
{

}

std::string HQ::getType() const
{
    return "HeadQuarters";
}

void HQ::onBuildAction()
{
    std::vector< std::shared_ptr<Course::TileBase> > neighbours =
            lockObjectManager()->getTiles(getCoordinatePtr()->neighbours(3));

    for(auto it = neighbours.begin(); it != neighbours.end(); ++it)
    {   
        // If the Tile doesn't have owner, set it's owner to buildings owner.
        if( not (*it)->getOwner() )
        {
            (*it)->setOwner(getOwner());
        }
    }
}
