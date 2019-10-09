#ifndef SAWMILL_HH
#define SAWMILL_HH

#include "buildings/buildingbase.h"

const Course::ResourceMap SAWMILL_BUILD_COST = {
    {Course::BasicResource::MONEY, 100},
    {Course::BasicResource::FOOD, 100},
    {Course::BasicResource::WOOD, 100}
};

const Course::ResourceMap SAWMILL_PRODUCTION =  {
    {Course::BasicResource::MONEY, 5},
    {Course::BasicResource::WOOD, 10}
};

class Sawmill : public Course::BuildingBase
{
public:
    Sawmill() = delete;
    explicit Sawmill(
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            const int& tilespaces = 1,
            const Course::ResourceMap& buildcost = SAWMILL_BUILD_COST,
            const Course::ResourceMap& production = SAWMILL_PRODUCTION
            );

    virtual ~Sawmill() = default;

    virtual std::string getType() const override;
};

#endif // SAWMILL_HH
