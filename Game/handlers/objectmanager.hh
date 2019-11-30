#ifndef OBJECTMANAGER_HH
#define OBJECTMANAGER_HH

#include "interfaces/iobjectmanager.h"
#include "interfaces/igameeventhandler.h"
#include "core/coordinate.h"
#include "core/gameobject.h"
#include "tiles/tilebase.h"
#include "tiles/extendedtilebase.h"
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
                  std::shared_ptr<Course::iGameEventHandler> gameEventHandler = nullptr,
                  std::shared_ptr<WorldScene> scene = nullptr);

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

    /**
     * @brief addTiles Only used by worldgeneration, this adds all game tiles
     * into its internal list
     * @param tiles
     */
    virtual void addTiles(const std::vector<std::shared_ptr<Course::TileBase>> &tiles);

    /**
     * @brief getTile finds a tile with the given coordinates
     * @param coordinate
     * @return pointer to the tile
     * @exception InvalidCoordinate if given coordinates are outside map limits
     */
    virtual std::shared_ptr<Course::TileBase> getTile(const Course::Coordinate& coordinate);

    /**
     * @brief getTile searches its inner list for an item with the given ID
     * @param id
     * @return pointer to the tile with same ID
     */
    virtual std::shared_ptr<Course::TileBase> getTile(const Course::ObjectId& id);

    /**
     * @brief getTiles is the same as getTile but can get multiple tiles simultaneously
     * @param coordinates a vector of wanted coordinates
     * @return a vector of pointers to the found tiles
     * @exception InvalidCoordinate if given coordinates are outside map limits
     */
    virtual std::vector<std::shared_ptr<Course::TileBase>> getTiles(
            const std::vector<Course::Coordinate>& coordinates);

    /**
     * @brief constructBuilding makes a new building with the given parameters
     * @param type string identifier as to which building type to make
     * @param location Coordinate to where the building is being built.
     * @param owner Shared pointer to building owner
     * @exception Course::BaseException if type is not recognized
     * @exception InvalidCoordinate if given coordinates are outside map limits
     */
    void constructBuilding(std::string type, Course::Coordinate location,
                           std::shared_ptr<Player> owner);

    /**
     * @brief addBuilding adds a pre-existing building to internal list
     * @param building Shared pointer to building
     */
    void addBuilding(const std::shared_ptr<UpgradeableBuilding> &building);

    /**
     * @brief removeBuilding removes the building with given ID from objManager
     * @param ID identifier for the building to be removed
     * @return true if successful
     */
    bool removeBuilding(Course::ObjectId ID);

    /**
     * @brief constructUnit Makes a new unit with the given parameters
     * @param type string identifier as to what type of unit to make
     * @param location Coordinate to where the unit is created
     * @param owner Shared pointer to unit owner
     * @exception InvalidCoordinate if given coordinates are outside map limits
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

    /**
     * @brief progressResearch updates Research values done in Campus, and checks
     * if player has won the game by completing research.
     * @param owner the player whose turn it is
     * @return true if research complete
     */
    bool progressResearch(std::shared_ptr<Player> owner);

    /**
     * @brief getPlayerScouts returns a list of all scouts that the player owns,
     * to make it easier to determine which tiles the player can build on
     * @param player the player whose scouts are listed
     * @return a list of pointers to scouts
     */
    std::vector<std::shared_ptr<UnitBase>> getPlayerScouts(std::shared_ptr<Player> player);

    /**
     * @brief getUnitsOnCoord needed by Campus to calculate progress speed, returns
     * a list of workers that are at the given coordinates
     * @param loc
     * @return a list of workers
     */
    std::vector<std::shared_ptr<Course::WorkerBase>> getUnitsOnCoord(Course::Coordinate loc);

    /**
     * @brief getPlayerZone gets a list of coordinates to all tiles owned by given player
     * @param player the current player
     * @return a list of all coordinates
     */
    std::vector<Course::Coordinate> getPlayerZone(std::shared_ptr<Player> player);

    /**
     * @brief getBuildings returns a full list of all buildings
     * @return _buildings
     */
    std::vector<std::shared_ptr<UpgradeableBuilding>> getBuildings();

    /**
     * @brief getUnits returns a full list of all units
     * @return _units
     */
    std::vector<std::shared_ptr<UnitBase>> getUnits();

private:
    /**
     * @brief checkCoordinate ensures given coordinates are within map limits
     * before they're used in the code
     * @param coord
     * @exception InvalidCoordinate if given coordinates are outside map limits
     */
    void checkCoordinate(Course::Coordinate coord);

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
