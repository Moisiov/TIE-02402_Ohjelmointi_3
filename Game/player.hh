#ifndef PLAYER_HH
#define PLAYER_HH

#include "core/playerbase.h"
#include "basicinfo.hh"
#include "tiles/tilebase.h"
#include "buildings/upgradeablebuilding.hh"
#include "workers/unitbase.hh"

enum PlayerColor { RED, BLUE, GREEN, ORANGE, PURPLE, CYAN };

/**
 * @brief The Player class handles player-related data, such as its name, chosen color,
 * and current resources.
 */
class Player: public Course::PlayerBase
{
public:
    Player() = delete;

    /**
     * @brief Player constructor requires a name and a color value
     */
    Player(const std::string& name,
           PlayerColor color,
           const std::vector<std::shared_ptr<Course::GameObject>> objects = {});

    /**
     * @brief Player alternative constructor to give different starting resources from default.
     */
    Player(const std::string& name,
           PlayerColor color,
           const Course::ResourceMap& startingResources,
           const std::vector<std::shared_ptr<Course::GameObject>> objects = {});

    ~Player() = default;

    void addTile(std::shared_ptr<Course::TileBase> tile);

    void addBuilding(std::shared_ptr<UpgradeableBuilding> building);

    void addUnit(std::shared_ptr<UnitBase> unit);

    /**
     * @brief getResources returns a full list of the players current materials
     * @return Course::ResourceMap
     */
    Course::ResourceMap getResources();

    /**
     * @brief getColor returns players chosen color
     * @return PlayerColor
     */
    PlayerColor getColor();

    /**
     * @brief canAfford checks if player has enough resources to afford a purchase
     * @param cost the amount of resources needed
     * @pre Only have each material in the list once, function doesn't support duplicate entries
     * @return boolean, true if can afford
     */
    bool canAfford(Course::ResourceMap cost);

    /**
     * @brief modifyResource changes one of the resources by given amount
     * @param resource the resource to be modified
     * @param amount how much to modify it
     * @return boolean, true if players resources still all in positives after exchange
     */
    bool modifyResource(Course::BasicResource resource, int amount);

    /**
     * @brief modifyResources changes a list of resources by given amount
     * @param resources the a list of resources to be modified
     * @return boolean, true if players resources still all in positives after exchange
     */
    bool modifyResources(Course::ResourceMap resources);

    void setHQCoord(Course::Coordinate coord);

    Course::Coordinate getHQCoord();

private:
    Course::ResourceMap _resources;
    PlayerColor _color;
    std::vector<std::shared_ptr<Course::TileBase>> _ownedTiles;
    std::vector<std::shared_ptr<UpgradeableBuilding>> _ownedBuildings;
    std::vector<std::shared_ptr<UnitBase>> _ownedUnits;
    Course::Coordinate _HQCoord;
};

#endif // PLAYER_HH
