#ifndef MARKET_HH
#define MARKET_HH

#include "buildings/buildingbase.h"

const Course::ResourceMap MARKET_BUILD_COST = {
    {Course::BasicResource::MONEY, 100},
    {Course::BasicResource::FOOD, 100},
    {Course::BasicResource::WOOD, 100}
};
const Course::ResourceMap MARKET_PRODUCTION = {
    {Course::BasicResource::MONEY, 10}
};

class Market : public Course::BuildingBase
{
public:
    Market() = delete;

    explicit Market(
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            const int& tilespaces = 1,
            const Course::ResourceMap& buildcost = MARKET_BUILD_COST,
            const Course::ResourceMap& production = MARKET_PRODUCTION
            );

    virtual ~Market() = default;

    virtual std::string getType() const override;
};

#endif // MARKET_HH
