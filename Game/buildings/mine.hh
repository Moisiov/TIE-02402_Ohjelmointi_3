#ifndef MINE_HH
#define MINE_HH

#include "upgradeablebuilding.hh"
#include "basicinfo.hh"

class Mine : public UpgradeableBuilding
{
public:
    Mine() = delete;

    explicit Mine(
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            const int& tilespaces = 1,
            const std::vector<Course::ResourceMap>& buildcost = MINE_BUILD_COST_LIST,
            const std::vector<Course::ResourceMap>& production = MINE_PRODUCTION_LIST,
            const unsigned int maxTier = 3
            );

    virtual ~Mine() = default;

    virtual std::string getType() const override;
};

#endif // MINE_HH
