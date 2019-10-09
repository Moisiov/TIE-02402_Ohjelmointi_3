#ifndef MARKET_HH
#define MARKET_HH

#include "upgradeablebuilding.hh"

const std::vector<Course::ResourceMap> MARKET_BUILD_COST_LIST = {
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
const std::vector<Course::ResourceMap> MARKET_PRODUCTION_LIST = {
    {
        {Course::BasicResource::MONEY, 10}
    },
    {
        {Course::BasicResource::MONEY, 20}
    },
    {
        {Course::BasicResource::MONEY, 30}
    }
};

class Market : public UpgradeableBuilding
{
public:
    Market() = delete;

    explicit Market(
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            const int& tilespaces = 1,
            const std::vector<Course::ResourceMap>& buildcost = MARKET_BUILD_COST_LIST,
            const std::vector<Course::ResourceMap>& production = MARKET_PRODUCTION_LIST,
            const unsigned int maxTier = 3
            );

    virtual ~Market() = default;

    virtual std::string getType() const override;
};

#endif // MARKET_HH
