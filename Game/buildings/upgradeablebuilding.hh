#ifndef UPGRADEABLEBUILDING_HH
#define UPGRADEABLEBUILDING_HH

#include "buildings/buildingbase.h"
#include "core/resourcemaps.h"
#include <vector>

class UpgradeableBuilding : public Course::BuildingBase
{
public:
    UpgradeableBuilding() = delete;

    explicit UpgradeableBuilding(
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            const int& tilespaces,
            const std::vector<Course::ResourceMap>& buildcost,
            const std::vector<Course::ResourceMap>& production,
            const unsigned int maxTier
            );

    virtual ~UpgradeableBuilding() = default;

    virtual Course::ResourceMap getProduction() final;

    unsigned int getUpgradeTier() const;

    bool isUpgradeable() const;

    const Course::ResourceMap& getUpgradeCost() const;

    void upgradeBuilding();

    Course::ResourceMap getSellValue();

    std::string description();

private:
    unsigned int tier_;
    const unsigned int maxTier_;
    const std::vector<Course::ResourceMap>& buildcost_;
    const std::vector<Course::ResourceMap>& production_;
};

#endif // UPGRADEABLEBUILDING_HH
