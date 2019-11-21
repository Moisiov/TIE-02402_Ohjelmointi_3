#ifndef SWAMP_HH
#define SWAMP_HH

#include "extendedtilebase.h"
#include "basicinfo.hh"

/**
 * @brief The Swamp class represents swamp in the gameworld.
 */
class Swamp : public ExtendedTileBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    Swamp() = delete;

    /**
     * @brief Constructor for the class Swamp
     * @param location is the coordinate where the tile is located
     * @param eventhandler points to the GameEvenHandler
     * @param objectmanager points to the ObjectHandler
     */
    Swamp(const Course::Coordinate& location,
         const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
         const std::shared_ptr<Course::iObjectManager>& objectmanager,
         const unsigned int& max_build = 1,
         const unsigned int& max_work = 3,
         const Course::ResourceMap& production = SWAMP_PROD,
         const std::vector<std::string>& buildableBuildings = SWAMP_BUILD);

    /**
     * @brief Default destructor.
     */
    virtual ~Swamp() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;
};

#endif // SWAMP_HH
