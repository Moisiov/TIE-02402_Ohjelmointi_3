#ifndef WATER_HH
#define WATER_HH


#include "tiles/tilebase.h"
#include "basicinfo.hh"

/**
 * @brief The Water class represents water in the gameworld.
 */
class Water : public Course::TileBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    Water() = delete;

    /**
     * @brief Constructor for the class Water
     * @param location is the coordinate where the tile is located
     * @param eventhandler points to the GameEvenHandler
     * @param objectmanager points to the ObjectHandler
     */
    Water(const Course::Coordinate& location,
         const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
         const std::shared_ptr<Course::iObjectManager>& objectmanager,
         const unsigned int& max_build = 1,
         const unsigned int& max_work = 3,
         const Course::ResourceMap& production = WATER_PROD);

    /**
     * @brief Default destructor.
     */
    virtual ~Water() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;
};

#endif // WATER_HH
