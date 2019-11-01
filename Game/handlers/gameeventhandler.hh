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
     * @brief setPlayerList Players initialized in MapWindow, pointers given here
     * @param playerList
     */
    void setPlayerList(std::vector<std::shared_ptr<Player>> playerList);

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
};

#endif // GAMEEVENTHANDLER_HH
