#ifndef EXTENDEDTILEBASE_H
#define EXTENDEDTILEBASE_H

#include "tiles/tilebase.h"
#include "basicinfo.hh"

/**
 * @brief The ExtendedTileBase class redefines resource generation from TileBase
 * and acts as an umbrella for all tile-types used in the game
 */
class ExtendedTileBase : public Course::TileBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    ExtendedTileBase() = delete;

    /**
     * @brief Constructor for the class.
     *
     */
    ExtendedTileBase(const Course::Coordinate& location,
             const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
             const std::shared_ptr<Course::iObjectManager>& objectmanager,
             const unsigned int& max_build = 1,
             const unsigned int& max_work = 3,
             const Course::ResourceMap& production = {},
             const std::vector<std::string>& buildableBuildings = {}
             );

    /**
     * @brief getBuildableBuildings
     * @return vector containing buildable building types
     */
    std::vector<std::string> getBuildableBuildings();

    /**
     * @brief description returns a short description about the tile for tooltip purposes
     * @return a short description
     */
    std::string description();

    /**
     * @brief calculateProduction uses a different calculation method to determine
     * how much the tile produces, based on (tile + building bonus) * worker multipliers
     * @return ResourceMap to how much tile currently produces
     */
    Course::ResourceMap calculateProduction();

    /**
     * @brief generateResources calls calculateProduction and gives that much resources
     * to the owner
     * @return true if successful
     */
    virtual bool generateResources() override;

private:
    std::vector<std::string> _buildableBuildings;
};

#endif // EXTENDEDTILEBASE_H
