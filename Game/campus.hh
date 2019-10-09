#ifndef CAMPUS_HH
#define CAMPUS_HH

#include "buildings/buildingbase.h"

const Course::ResourceMap CAMPUS_BUILD_COST = {
    {Course::BasicResource::MONEY, 1000},
    {Course::BasicResource::FOOD, 1000},
    {Course::BasicResource::WOOD, 1000},
    {Course::BasicResource::STONE, 1000},
    {Course::BasicResource::ORE, 1000}

};
const Course::ResourceMap CAMPUS_PRODUCTION = {}; // Intentionally empty

class Campus : Course::BuildingBase
{
public:
    Campus() = delete;

    /**
     * @brief Campus
     *
     * @param eventhandler
     * @param objectmanager
     * @param owner
     * @param tilespaces Default value of 3, requires 3 empty building slots on the tile
     * @param buildcost Default values defined in campus.hh
     * @param production Default values defined in campus.hh
     *
     * @post Exception Guarantee: No guarantee.
     */
    explicit Campus(
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            const int& tilespaces = 3,
            const Course::ResourceMap& buildcost = CAMPUS_BUILD_COST,
            const Course::ResourceMap& production = CAMPUS_PRODUCTION
            );

    virtual ~Campus() = default;

    virtual std::string getType() const override;
};

#endif // CAMPUS_HH
