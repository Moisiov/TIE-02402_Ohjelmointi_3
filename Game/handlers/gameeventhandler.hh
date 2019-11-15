#ifndef GAMEEVENTHANDLER_HH
#define GAMEEVENTHANDLER_HH

#include "interfaces/igameeventhandler.h"
#include "objectmanager.hh"
#include "player.hh"

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



private:
    std::shared_ptr<ObjectManager> _objM; // To be filled in by setObjectManager call
    std::shared_ptr<GameEventHandler> _GEHandler;
    std::vector<std::shared_ptr<Player>> _playerList; // to be filled in by setPlayerList call
    unsigned _currentPlayer; // starts from zero, loops over _playerList count
    unsigned _map_x;
    unsigned _map_y;
};

#endif // GAMEEVENTHANDLER_HH
