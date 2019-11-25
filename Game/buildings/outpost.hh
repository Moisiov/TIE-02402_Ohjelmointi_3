#ifndef OUTPOST_HH
#define OUTPOST_HH

#include "upgradeablebuilding.hh"
#include "basicinfo.hh"

class Outpost: public UpgradeableBuilding
{
public:
    Outpost(const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
       const std::shared_ptr<Course::iObjectManager>& objectmanager,
       const std::shared_ptr<Course::PlayerBase>& owner,
       const int& tilespaces = 1,
       const std::vector<Course::ResourceMap>& buildcost = OUTPOST_BUILD_COST_LIST,
       const std::vector<Course::ResourceMap>& production = OUTPOST_PRODUCTION_LIST,
       const unsigned int maxTier = 3);

    virtual std::string getType() const override;

    virtual void onBuildAction() override;
};

#endif // OUTPOST_HH
