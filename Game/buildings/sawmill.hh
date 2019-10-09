#ifndef SAWMILL_HH
#define SAWMILL_HH

#include "upgradeablebuilding.hh"

const std::vector<Course::ResourceMap> SAWMILL_BUILD_COST_LIST =  {
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

const std::vector<Course::ResourceMap> SAWMILL_PRODUCTION_LIST = {
    {
        {Course::BasicResource::MONEY, 5},
        {Course::BasicResource::WOOD, 10}
    },
    {
        {Course::BasicResource::MONEY, 10},
        {Course::BasicResource::WOOD, 20}
    },
    {
        {Course::BasicResource::MONEY, 15},
        {Course::BasicResource::WOOD, 30}
    }
};

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
