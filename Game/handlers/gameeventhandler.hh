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
    void initializeGame(std::vector<std::shared_ptr<Player>> playerList, unsigned map_x, unsigned map_y);

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

private:
    std::shared_ptr<ObjectManager> _objM; // To be filled in by setObjectManager call
    std::vector<std::shared_ptr<Player>> _playerList; // to be filled in by setPlayerList call
    unsigned _currentPlayer; // starts from zero, loops over _playerList count
    unsigned _map_x;
    unsigned _map_y;
};

#endif // GAMEEVENTHANDLER_HH
