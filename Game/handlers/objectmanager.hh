#ifndef OBJECTMANAGER_HH
#define OBJECTMANAGER_HH

#include "interfaces/iobjectmanager.h"
#include "interfaces/igameeventhandler.h"
#include "core/coordinate.h"
#include "core/gameobject.h"
#include "tiles/tilebase.h"
#include "graphics/simplegamescene.h"

/**
 * @brief The ObjectManager class handles Course-side code
 * and it's derived from interface iObjectMAnager
 */
class ObjectManager : public Course::iObjectManager
{
public:
    ObjectManager(unsigned map_x = 0, unsigned map_y = 0, std::shared_ptr<Course::iGameEventHandler> gameEventHandler = {});

    /**
     * @brief Default destructor.
     */
    virtual ~ObjectManager() = default;

    /**
     * @brief setGEHandler sets the game event handler
     * @param gameEventHandler points to the GameEventHandler
     */
    void setGEHandler(std::shared_ptr<Course::iGameEventHandler> gameEventHandler);

    /**
     * @brief setMapSize sets the map size
     * @param map_x is the width of the map
     * @param map_y is the height of the map
     */
    void setMapSize(unsigned map_x, unsigned map_y);

    virtual void addTiles(const std::vector<std::shared_ptr<Course::TileBase>> &tiles);

    virtual std::shared_ptr<Course::TileBase> getTile(const Course::Coordinate& coordinate);

    virtual std::shared_ptr<Course::TileBase> getTile(const Course::ObjectId& id);

    virtual std::vector<std::shared_ptr<Course::TileBase>> getTiles(
            const std::vector<Course::Coordinate>& coordinates);

    // Not working yet
    void drawMap(std::shared_ptr<Course::SimpleGameScene> gameScene);



private:
    unsigned _map_x; // The x length of map
    unsigned _map_y; // The y length of map
    std::vector<std::shared_ptr<Course::GameObject>> _objects;
    std::vector<std::vector<std::shared_ptr<Course::TileBase>>> _tiles; // Tile pointers in nested vector according to coordinates
    std::shared_ptr<Course::iGameEventHandler> _gameEventHandler;
};

#endif // OBJECTMANAGER_HH
