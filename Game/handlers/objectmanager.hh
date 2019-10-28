#ifndef OBJECTMANAGER_HH
#define OBJECTMANAGER_HH

#include "interfaces/iobjectmanager.h"

/**
 * @brief The ObjectManager class handles Course-side code
 * and it's derived from interface iObjectMAnager
 */
class ObjectManager :  Course::iObjectManager
{
public:
    ObjectManager();

    /**
     * @brief Default destructor.
     */
    virtual ~ObjectManager() = default;

    virtual void addTiles(const std::vector<std::shared_ptr<Course::TileBase> > &tiles);

    virtual std::shared_ptr<Course::TileBase> getTile(const Course::Coordinate& coordinate);

    virtual std::shared_ptr<Course::TileBase> getTile(const Course::ObjectId& id);

    virtual std::vector<std::shared_ptr<Course::TileBase>> getTiles(
            const std::vector<Coordinate>& coordinates);

private:
    std::vector<std::shared_ptr<Course::GameObject>> _objects;
};

#endif // OBJECTMANAGER_HH
