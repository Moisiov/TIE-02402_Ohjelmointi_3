#ifndef SWAMP_HH
#define SWAMP_HH

#include "tiles/tilebase.h"

// TODO: add pointers to the GameEventHandler and ObjectManager

/**
 * @brief The Swamp class represents swamp in the gameworld.
 */
class Swamp : public Course::TileBase
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
         const unsigned int& max_build = 2,
         const unsigned int& max_work = 3,
         const Course::ResourceMap& production = Course::ConstResourceMaps::FOREST_BP);

    /**
     * @brief Default destructor.
     */
    virtual ~Swamp() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

    /**
     * @brief Adds a new building-object to the tile. Building in swamp adds
     * one hold-marker to the building.
     *
     * Phases: \n
     * 1. Check that there is space for the building. \n
     * 2. Call parent's addBuilding \n
     * 3. Add a HoldMarker for the building. \n
     *
     * @post Exception guarantee: Strong
     * @exception OwnerConflict - If the tile's ownership prevents placing the
     * \b building.
     * @exception NoSpace - If the tile doesn't have enough space for
     * the \b building.
     */
    void addBuilding(const std::shared_ptr<Course::BuildingBase>& building) override;
};

#endif // SWAMP_HH
