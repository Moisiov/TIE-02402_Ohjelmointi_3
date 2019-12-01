#ifndef UPGRADEABLEBUILDING_HH
#define UPGRADEABLEBUILDING_HH

#include "buildings/buildingbase.h"
#include "core/resourcemaps.h"
#include <vector>

/**
 * @brief The UpgradeableBuilding class extends BuildingBase by adding building
 * upgrading and selling.
 */
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

    /**
     * @brief getProduction returns how much extra production the building provides
     * @return ResourceMap to increased production
     */
    virtual Course::ResourceMap getProduction() final;

    /**
     * @brief getUpgradeTier tells what upgrade tier building currently is. All
     * buildings start at tier 1, and most buildings can be upgraded up to tier 3.
     * @return current upgrade tier
     */
    unsigned int getUpgradeTier() const;

    /**
     * @brief isUpgradeable checks if the building has reached its maximmum tier.
     * @return true if can still be upgraded
     */
    bool isUpgradeable() const;

    /**
     * @brief getUpgradeCost tells how much it costs to upgrade the building to
     * its next tier
     * @return ResourceMap to upgrade cost
     */
    const Course::ResourceMap& getUpgradeCost() const;

    /**
     * @brief upgradeBuilding increases the buildings upgrade tier
     */
    void upgradeBuilding();

    /**
     * @brief getSellValue calculates how much resources the player can get back
     * for selling the building, a total of 50% its original value
     * @return ResourceMap of sell value
     */
    Course::ResourceMap getSellValue();

    /**
     * @brief description defines a simple description for tooltip purposes
     * @return a short description
     */
    std::string description();

private:
    unsigned int tier_;
    const unsigned int maxTier_;
    const std::vector<Course::ResourceMap>& buildcost_;
    const std::vector<Course::ResourceMap>& production_;
};

#endif // UPGRADEABLEBUILDING_HH
