#include "upgradeablebuilding.hh"
#include "basicinfo.hh"
#include "player.hh"

UpgradeableBuilding::UpgradeableBuilding(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
                                         const std::shared_ptr<Course::iObjectManager> &objectmanager,
                                         const std::shared_ptr<Course::PlayerBase> &owner,
                                         const int &tilespaces,
                                         const std::vector<Course::ResourceMap> &buildcost,
                                         const std::vector<Course::ResourceMap> &production,
                                         const unsigned int maxTier
                                         ):
    Course::BuildingBase(eventhandler, objectmanager,  owner, tilespaces, buildcost.at(0), production.at(0)),
    tier_(1),
    maxTier_(maxTier),
    buildcost_(buildcost),
    production_(production)
{
    if (buildcost_.size() != maxTier || production_.size() != maxTier) {
        // Mismatch in constructor info, throw an error here later!
    }
}

Course::ResourceMap UpgradeableBuilding::getProduction()
{
    return production_.at(tier_ - 1);
}

unsigned int UpgradeableBuilding::getUpgradeTier() const
{
    return tier_;
}

bool UpgradeableBuilding::isUpgradeable() const
{
    if (tier_ < maxTier_) {
        return true;
    } else {
        return false;
    }
}

const Course::ResourceMap &UpgradeableBuilding::getUpgradeCost() const
{
    if (tier_ <= 0 || tier_ >= maxTier_) {
        return Course::ConstResourceMaps::EMPTY;
    }
    return buildcost_.at(tier_);
}

void UpgradeableBuilding::upgradeBuilding()
{
    if (tier_ >= maxTier_) {
        // Already at max tier, throw an error here later!
    }

    tier_ += 1;

    // Holding production for 1 turn while under construction
    addHoldMarkers(1);
}

Course::ResourceMap UpgradeableBuilding::getSellValue()
{
    Course::ResourceMap totalBuildCost = Course::ConstResourceMaps::EMPTY;

    for (unsigned i = 0; i < tier_; ++i) {
        totalBuildCost = Course::mergeResourceMaps(totalBuildCost, buildcost_[i]);
    }

    Course::ResourceMap sellValue = Course::multiplyResourceMap(totalBuildCost, HALF);
    return sellValue;
}

std::string UpgradeableBuilding::description()
{
    std::string description = "";
    description += getOwner()->getName() + "'s " + getType();
    if (maxTier_ > 1) {
        description += ", tier: " + std::to_string(tier_);
    }

    return description;
}
