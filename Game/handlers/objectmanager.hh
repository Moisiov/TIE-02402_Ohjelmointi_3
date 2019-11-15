#ifndef OBJECTMANAGER_HH
#define OBJECTMANAGER_HH

#include "interfaces/iobjectmanager.h"
#include "interfaces/igameeventhandler.h"
#include "core/coordinate.h"
#include "core/gameobject.h"
#include "tiles/tilebase.h"
#include "graphics/worldscene.h"
#include "buildings/upgradeablebuilding.hh"
#include "workers/unitbase.hh"
#include "player.hh"

/**
 * @brief The ObjectManager class handles Course-side code
 * and it's derived from interface iObjectMAnager
 */
class ObjectManager : public Course::iObjectManager
{
public:
    ObjectManager(unsigned map_x = 0, unsigned map_y = 0,
                  std::shared_ptr<Course::iGameEventHandler> gameEventHandler = {},
                  std::shared_ptr<WorldScene> scene = {});

    /**
     * @brief Default destructor.
     */
    virtual ~ObjectManager() = default;

    /**
     * @brief setGEHandler sets the game event handler
     * @param gameEventHandler points to the GameEventHandler
     */
    void setGEHandler(std::shared_ptr<Course::iGameEventHandler> gameEventHandler);

    void setObjManager(std::shared_ptr<ObjectManager> objectManager);

    /**
     * @brief setMapSize sets the map size
     * @param map_x is the width of the map
     * @param map_y is the height of the map
     */
    void setMapSize(unsigned map_x, unsigned map_y);

    /**
     * @brief setScene sets the scene
     * @param scene points to the world scene
     */
    void setScene(std::shared_ptr<WorldScene> scene);

    virtual void addTiles(const std::vector<std::shared_ptr<Course::TileBase>> &tiles);

    virtual std::shared_ptr<Course::TileBase> getTile(const Course::Coordinate& coordinate);

    virtual std::shared_ptr<Course::TileBase> getTile(const Course::ObjectId& id);

    virtual std::vector<std::shared_ptr<Course::TileBase>> getTiles(
            const std::vector<Course::Coordinate>& coordinates);

    /**
     * @brief constructBuilding makes a new building with the given parameters
     * @param type string identifier as to which building type to make
     * @param location Coordinate to where the building is being built.
     * @param owner Shared pointer to building owner
     */
    void constructBuilding(std::string type, Course::Coordinate location,
                           std::shared_ptr<Player> owner);

    /**
     * @brief addBuilding adds a pre-existing building to internal list
     * @param building Shared pointer to building
     */
    void addBuilding(const std::shared_ptr<UpgradeableBuilding> &building);

    /**
     * @brief constructUnit Makes a new unit with the given parameters
     * @param type string identifier as to what type of unit to make
     * @param location Coordinate to where the unit is created
     * @param owner Shared pointer to unit owner
     */
    void constructUnit(std::string type, Course::Coordinate location,
                       std::shared_ptr<Player> owner);

    /**
     * @brief addUnit adds a pre-existing unit to internal list
     * @param unit Shared pointer to unit
     */
    void addUnit(const std::shared_ptr<UnitBase> &unit);

    void drawMap();

    void drawItem(std::shared_ptr<Course::GameObject> obj);

    /**
     * @brief restoreMoves restores moving ability to all units of the player
     * @param owner the player whose units should be updated
     */
    void restoreMoves(std::shared_ptr<Player> owner);

    /**
     * @brief generateResources calculates how much resources the player gained
     * in-between turns
     * @param owner the player whose resources need updating
     */
    void generateResources(std::shared_ptr<Player> owner);

private:
    unsigned _map_x; // The x length of map
    unsigned _map_y; // The y length of map
    std::vector<std::vector<std::shared_ptr<Course::TileBase>>> _tiles; // Tile pointers in nested vector according to coordinates
    std::vector<std::shared_ptr<UpgradeableBuilding>> _buildings;
    std::vector<std::shared_ptr<UnitBase>> _units;
    std::shared_ptr<Course::iGameEventHandler> _gameEventHandler;
    std::shared_ptr<Course::iObjectManager> _objectManager;
    std::shared_ptr<WorldScene> _scene;
};

#endif // OBJECTMANAGER_HH
