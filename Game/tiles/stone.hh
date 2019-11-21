#ifndef STONE_HH
#define STONE_HH

#include "extendedtilebase.h"
#include "basicinfo.hh"

/**
 * @brief The Stone class represents stone in the gameworld.
 */
class Stone : public ExtendedTileBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    Stone() = delete;

    /**
     * @brief Constructor for the class Stone
     * @param location is the coordinate where the tile is located
     * @param eventhandler points to the GameEvenHandler
     * @param objectmanager points to the ObjectHandler
     */
    Stone(const Course::Coordinate& location,
         const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
         const std::shared_ptr<Course::iObjectManager>& objectmanager,
         const unsigned int& max_build = 1,
         const unsigned int& max_work = 3,
         const Course::ResourceMap& production = STONE_PROD,
         const std::vector<std::string>& buildableBuildings = STONE_BUILD);

    /**
     * @brief Default destructor.
     */
    virtual ~Stone() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;
};

#endif // STONE_HH
