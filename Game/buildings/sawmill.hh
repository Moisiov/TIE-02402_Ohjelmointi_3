#ifndef SAWMILL_HH
#define SAWMILL_HH

#include "upgradeablebuilding.hh"
#include "basicinfo.hh"

class Sawmill : public UpgradeableBuilding
{
public:
    Sawmill() = delete;

    explicit Sawmill(
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            const int& tilespaces = 1,
            const std::vector<Course::ResourceMap>& buildcost = SAWMILL_BUILD_COST_LIST,
            const std::vector<Course::ResourceMap>& production = SAWMILL_PRODUCTION_LIST,
            const unsigned int maxTier = 3
            );

    virtual ~Sawmill() = default;

    virtual std::string getType() const override;
};

#endif // SAWMILL_HH
