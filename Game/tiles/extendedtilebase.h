#ifndef EXTENDEDTILEBASE_H
#define EXTENDEDTILEBASE_H

#include "tiles/tilebase.h"
#include "basicinfo.hh"

class ExtendedTileBase : Course::TileBase
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

private:
    std::vector<std::string> _buildableBuildings;
};

#endif // EXTENDEDTILEBASE_H
