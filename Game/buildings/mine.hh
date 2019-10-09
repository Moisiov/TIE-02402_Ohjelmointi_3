#ifndef MINE_HH
#define MINE_HH

#include "upgradeablebuilding.hh"

const std::vector<Course::ResourceMap> MINE_BUILD_COST_LIST = {
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

const std::vector<Course::ResourceMap> MINE_PRODUCTION_LIST {
    {
        {Course::BasicResource::STONE, 10},
        {Course::BasicResource::ORE, 5}
    },
    {
        {Course::BasicResource::STONE, 20},
        {Course::BasicResource::ORE, 10}
    },
    {
        {Course::BasicResource::STONE, 30},
        {Course::BasicResource::ORE, 15}
    }
};


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
