#ifndef GRASSLAND_H
#define GRASSLAND_H

#include "tiles/tilebase.h"
#include "basicinfo.hh"

class Grassland : public Course::TileBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    Grassland() = delete;

    /**
     * @brief Constructor for the class.
     *
     * @param location is the Coordinate where the Tile is located in the game.
     * @param eventhandler points to the student's GameEventHandler.
     */
    Grassland(const Course::Coordinate& location,
              const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
              const std::shared_ptr<Course::iObjectManager>& objectmanager,
              const unsigned int& max_build = 1,
              const unsigned int& max_work = 3,
              const Course::ResourceMap& production = GRASSLAND_PROD);

    /**
     * @brief Default destructor.
     */
    virtual ~Grassland() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;
};

#endif // GRASSLAND_H
