#ifndef CAMPUS_HH
#define CAMPUS_HH

#include "upgradeablebuilding.hh"

const std::vector<Course::ResourceMap> CAMPUS_BUILD_COST_LIST = {
    {
        {Course::BasicResource::MONEY, 1000},
        {Course::BasicResource::FOOD, 1000},
        {Course::BasicResource::WOOD, 1000},
        {Course::BasicResource::STONE, 1000},
        {Course::BasicResource::ORE, 1000}
    }
};

const std::vector<Course::ResourceMap> CAMPUS_PRODUCTION_LIST = {
  {} // Intentionally empty, no production
};

class Campus : UpgradeableBuilding
{
public:
    Campus() = delete;

    explicit Campus(
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            const int& tilespaces = 3,
            const std::vector<Course::ResourceMap>& buildcost = CAMPUS_BUILD_COST_LIST,
            const std::vector<Course::ResourceMap>& production = CAMPUS_PRODUCTION_LIST,
            const unsigned int maxTier = 1
            );

    virtual ~Campus() = default;

    virtual std::string getType() const override;
};

#endif // CAMPUS_HH
