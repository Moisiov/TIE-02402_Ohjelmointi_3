#ifndef FISHERY_HH
#define FISHERY_HH

#include "upgradeablebuilding.hh"

const std::vector<Course::ResourceMap> FISHERY_BUILD_COST_LIST = {
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

const Course::ResourceMap FISHERY_PRODUCTION = {
    {Course::BasicResource::MONEY, 5},
    {Course::BasicResource::FOOD, 10}
};

const std::vector<Course::ResourceMap> FISHERY_PRODUCTION_LIST = {
    {
        {Course::BasicResource::MONEY, 5},
        {Course::BasicResource::FOOD, 10}
    },
    {
        {Course::BasicResource::MONEY, 10},
        {Course::BasicResource::FOOD, 20}
    },
    {
        {Course::BasicResource::MONEY, 15},
        {Course::BasicResource::FOOD, 30}
    }
};

class Fishery : public UpgradeableBuilding
{
public:
    Fishery() = delete;

    explicit Fishery(
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            const int& tilespaces = 1,
            const std::vector<Course::ResourceMap>& buildcost = FISHERY_BUILD_COST_LIST,
            const std::vector<Course::ResourceMap>& production = FISHERY_PRODUCTION_LIST,
            const unsigned int maxTier = 3
            );

    virtual ~Fishery() = default;

    virtual std::string getType() const override;
};

#endif // FISHERY_HH
