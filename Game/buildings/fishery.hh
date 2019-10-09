#ifndef FISHERY_HH
#define FISHERY_HH

#include "buildings/buildingbase.h"

const Course::ResourceMap FISHERY_BUILD_COST = {
    {Course::BasicResource::MONEY, 100},
    {Course::BasicResource::FOOD, 100},
    {Course::BasicResource::WOOD, 100}
};
const Course::ResourceMap FISHERY_PRODUCTION = {
    {Course::BasicResource::MONEY, 5},
    {Course::BasicResource::FOOD, 10}
};

class Fishery : public Course::BuildingBase
{
public:
    Fishery() = delete;

    explicit Fishery(
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            const int& tilespaces = 1,
            const Course::ResourceMap& buildcost = FISHERY_BUILD_COST,
            const Course::ResourceMap& production = FISHERY_PRODUCTION
            );

    virtual ~Fishery() = default;

    virtual std::string getType() const override;
};

#endif // FISHERY_HH
