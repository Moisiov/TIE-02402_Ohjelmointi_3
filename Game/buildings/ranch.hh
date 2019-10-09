#ifndef RANCH_HH
#define RANCH_HH

#include "upgradeablebuilding.hh"

const std::vector<Course::ResourceMap> RANCH_BUILD_COST_LIST = {
    {
        {Course::BasicResource::MONEY, 100},
        {Course::BasicResource::FOOD, 100},
        {Course::BasicResource::WOOD, 100}
    },
    {
        {Course::BasicResource::MONEY, 100},
        {Course::BasicResource::FOOD, 100},
        {Course::BasicResource::WOOD, 100}
    },
    {
        {Course::BasicResource::MONEY, 100},
        {Course::BasicResource::FOOD, 100},
        {Course::BasicResource::WOOD, 100}
    }
};

const std::vector<Course::ResourceMap> RANCH_PRODUCTION_LIST = {
    {
        {Course::BasicResource::FOOD, 10}
    },
    {
        {Course::BasicResource::FOOD, 20}
    },
    {
        {Course::BasicResource::FOOD, 30}
    }
};

class Ranch : public UpgradeableBuilding
{
public:
    Ranch() = delete;

    explicit Ranch(
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            const int& tilespaces = 1,
            const std::vector<Course::ResourceMap>& buildcost = RANCH_BUILD_COST_LIST,
            const std::vector<Course::ResourceMap>& production = RANCH_PRODUCTION_LIST,
            const unsigned int maxTier = 3
            );

    virtual ~Ranch() = default;

    virtual std::string getType() const override;
};

#endif // RANCH_HH
