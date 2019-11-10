#ifndef HQ_HH
#define HQ_HH

#include "upgradeablebuilding.hh"
#include "basicinfo.hh"

class HQ: public UpgradeableBuilding
{
public:
    HQ(const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
       const std::shared_ptr<Course::iObjectManager>& objectmanager,
       const std::shared_ptr<Course::PlayerBase>& owner,
       const int& tilespaces = 1,
       const std::vector<Course::ResourceMap>& buildcost = HQ_BUILD_COST_LIST,
       const std::vector<Course::ResourceMap>& production = HQ_PRODUCTION_LIST,
       const unsigned int maxTier = 1);

    virtual std::string getType() const override;

    virtual void onBuildAction() override;
};

#endif // HQ_HH
