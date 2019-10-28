#ifndef OBJECTMANAGER_HH
#define OBJECTMANAGER_HH

#include "interfaces/iobjectmanager.h"
#include "interfaces/igameeventhandler.h"
#include "core/coordinate.h"
#include "core/gameobject.h"
#include "tiles/tilebase.h"

/**
 * @brief The ObjectManager class handles Course-side code
 * and it's derived from interface iObjectMAnager
 */
class ObjectManager :  Course::iObjectManager
{
public:
    ObjectManager(int map_size = 0, std::shared_ptr<Course::iGameEventHandler> gameEventHandler = {});

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
     * @param size is the length of one side in square map
     */
    void setMapSize(int size);

    virtual void addTiles(const std::vector<std::shared_ptr<Course::TileBase>> &tiles);

    virtual std::shared_ptr<Course::TileBase> getTile(const Course::Coordinate& coordinate);

    virtual std::shared_ptr<Course::TileBase> getTile(const Course::ObjectId& id);

    virtual std::vector<std::shared_ptr<Course::TileBase>> getTiles(
            const std::vector<Course::Coordinate>& coordinates);



private:
    int _map_size; // The length of one side of a square map
    std::vector<std::shared_ptr<Course::GameObject>> _objects;
    std::vector<std::vector<std::shared_ptr<Course::TileBase>>> _tiles; // Tile pointers in nested vector according to coordinates
    std::shared_ptr<Course::iGameEventHandler> _gameEventHandler;
};

#endif // OBJECTMANAGER_HH
