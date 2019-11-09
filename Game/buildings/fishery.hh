#ifndef FISHERY_HH
#define FISHERY_HH

#include "upgradeablebuilding.hh"
#include "basicinfo.hh"

class Fishery : public UpgradeableBuilding
{
public:
    Fishery() = delete;

    explicit Fishery(
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            const int& tilespaces = 1,
            const std::vector<Course::ResourceMap>& buildcost = FISHERY_BUILD_COST_LIST,
            const std::vector<Course::ResourceMap>& production = FISHERY_PRODUCTION_LIST,
            const unsigned int maxTier = 3
            );

    virtual ~Fishery() = default;

    virtual std::string getType() const override;
};

#endif // FISHERY_HH
