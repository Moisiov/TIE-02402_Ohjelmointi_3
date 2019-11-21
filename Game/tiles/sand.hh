#ifndef SAND_HH
#define SAND_HH

#include "extendedtilebase.h"
#include "basicinfo.hh"

/**
 * @brief The Sand class represents Sand in the gameworld.
 */
class Sand : public ExtendedTileBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    Sand() = delete;

    /**
     * @brief Constructor for the class Sand
     * @param location is the coordinate where the tile is located
     * @param eventhandler points to the GameEvenHandler
     * @param objectmanager points to the ObjectHandler
     */
    Sand(const Course::Coordinate& location,
         const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
         const std::shared_ptr<Course::iObjectManager>& objectmanager,
         const unsigned int& max_build = 1,
         const unsigned int& max_work = 3,
         const Course::ResourceMap& production = SAND_PROD,
         const std::vector<std::string>& buildableBuildings = SAND_BUILD);

    /**
     * @brief Default destructor.
     */
    virtual ~Sand() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;
};

#endif // SAND_HH
