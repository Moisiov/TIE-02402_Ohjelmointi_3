#ifndef MINE_HH
#define MINE_HH

#include "buildings/buildingbase.h"

const Course::ResourceMap MINE_BUILD_COST = {
    {Course::BasicResource::MONEY, 100},
    {Course::BasicResource::FOOD, 100},
    {Course::BasicResource::WOOD, 100}
};

const Course::ResourceMap MINE_PRODUCTION = {
    {Course::BasicResource::STONE, 10},
    {Course::BasicResource::ORE, 5}
};


class Mine : public Course::BuildingBase
{
public:
    Mine() = delete;

    explicit Mine(
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            const int& tilespaces = 1,
            const Course::ResourceMap& buildcost = MINE_BUILD_COST,
            const Course::ResourceMap& production = MINE_PRODUCTION
            );

    virtual ~Mine() = default;

    virtual std::string getType() const override;
};

#endif // MINE_HH
