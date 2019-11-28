#ifndef GAMEEVENTHANDLER_HH
#define GAMEEVENTHANDLER_HH

#include "interfaces/igameeventhandler.h"
#include "objectmanager.hh"
#include "player.hh"
#include "workers/worker.hh"

class GameEventHandler : public Course::iGameEventHandler
{
public:
    /**
     * @brief GameEventHandler constructor
     */
    GameEventHandler();
    ~GameEventHandler() = default;

    /**
     * @brief setGEHandler getting a pointer to itselt to share with new objects
     * as they're created
     * @param GEHandler
     */
    void setGEHandler(std::shared_ptr<GameEventHandler> GEHandler);

    /**
     * @brief setObjectManager ObjManager built after GameEventHandler, pointer given here
     * @param objM
     */
    void setObjectManager(std::shared_ptr<ObjectManager> objM);

    /**
     * @brief initializeGame initializes the starting locations, buildings and units
     * @param playerList initial Player classes constructed within mapwindow
     * @param map_x Map width
     * @param map_y Map height
     */
    void initializeGame(std::vector<std::string> playerNames,
                        std::vector<PlayerColor> playerColors,
                        unsigned map_x,
                        unsigned map_y);

    /**
     * @brief modifyResource required by iGameEventHandler interface, it simply redirects
     * the call to the Player class which manages its own resources
     * @param player
     * @param resource
     * @param amount
     * @return boolean, true if players resources all in positive after change
     */
    virtual bool modifyResource(std::shared_ptr<Course::PlayerBase> player,
                                Course::BasicResource resource,
                                int amount);

    /**
     * @brief modifyResources required by iGameEventHandler interface, it simply redirects
     * the call to the Player class which manages its own resources
     * @param player
     * @param resources
     * @return boolean, true if players resources all in positive after change
     */
    virtual bool modifyResources(std::shared_ptr<Course::PlayerBase> player,
                                 Course::ResourceMap resources);

    /**
     * @brief currentTurn tells the number corresponding to the player whose turn it is
     */
    unsigned currentTurn();

    /**
     * @brief currentPlayer returns pointer to the player whose turn it currently is
     * @return shared_ptr
     */
    std::shared_ptr<Player> currentPlayer();

    /**
     * @brief endTurn gets called when player chooses to end their turn. This
     * function resets pawn moves, generates resources and handles any potential
     * events.
     */
    void endTurn();

    /**
     * @brief gameWon checks if the current player has earned enough campus research
     * to finish the game
     * @return true if game won
     */
    bool gameWon();

    /**
     * @brief canBuildOnTile checks if current player is allowed to build on a tile
     * @param type the building type
     * @param location the coordinates to the tile
     * @return true if possible
     */
    bool canBuildOnTile(std::string type, Course::Coordinate location);

    /**
     * @brief scoutOnUnownedTile checks if current player has a scout in an unowned tile
     * @param location is the coordinate to selected tile
     * @return true if has scout
     */
    bool scoutOnUnownedTile(Course::Coordinate location);

    /**
     * @brief constructBuilding checks if current player can construct a new
     * building at the given coordinates, and makes one if possible
     * @param type the string identifier for building type
     * @param location coordinates to where user wants the building
     * @return true if building successful
     */
    bool constructBuilding(std::string type, Course::Coordinate location);

    /**
     * @brief upgradeBuilding checks if current player can upgrade the given
     * building to next tier
     * @param building shared pointer to the building
     * @return true if upgrade successful
     */
    bool upgradeBuilding(std::shared_ptr<Course::BuildingBase> building);

    /**
     * @brief removeBuilding removes the building from the game and refunds
     * half of the original cost in materials
     * @param building shared pointer to the building to be sold
     */
    void sellBuilding(std::shared_ptr<Course::BuildingBase> building);

    /**
     * @brief constructUnit checks if the current player can create a new unit
     * in their HQ and does it
     * @param type string identifier for the unit to be built
     * @return true if successful
     */
    bool constructUnit(std::string type);

    /**
     * @brief moveUnit checks if the given pawn can move to the destination and
     * then moves it if possible
     * @param unit shared pointer to the pawn
     * @param destination coordinates to where player wants to move it
     * @return true if successful
     */
    bool moveUnit(std::shared_ptr<UnitBase> unit, Course::Coordinate destination);

    /**
     * @brief specializeUnit attempts to upgrade a Worker to a specialist
     * @param unit worker to be upgraded
     * @param specialization what type to specialize into
     * @return true if successful
     */
    bool specializeUnit(std::shared_ptr<Worker> unit, std::string specialization);

    /**
     * @brief getCurrentPlayerZone returns a vector of all current players owned
     * tiles for MapWindows highlight method
     * @return a vector of coordinates to all owned tiles
     */
    std::vector<Course::Coordinate> getCurrentPlayerZone();

private:
    std::shared_ptr<ObjectManager> _objM; // To be filled in by setObjectManager call
    std::shared_ptr<GameEventHandler> _GEHandler;
    std::vector<std::shared_ptr<Player>> _playerList; // to be filled in by setPlayerList call
    unsigned _currentPlayer; // starts from zero, loops over _playerList count
    unsigned _turn;
    unsigned _map_x;
    unsigned _map_y;
};

#endif // GAMEEVENTHANDLER_HH
