#ifndef GAMEEVENTHANDLER_HH
#define GAMEEVENTHANDLER_HH

#include "interfaces/igameeventhandler.h"
#include "objectmanager.hh"
#include "player.hh"

class GameEventHandler : public Course::iGameEventHandler
{
public:
    GameEventHandler();
    ~GameEventHandler() = default;

    void setObjectManager(std::shared_ptr<ObjectManager> objM);

    void setPlayerList(std::vector<std::shared_ptr<Player>> playerList);

    virtual bool modifyResource(std::shared_ptr<Course::PlayerBase> player,
                                Course::BasicResource resource,
                                int amount);

    virtual bool modifyResources(std::shared_ptr<Course::PlayerBase> player,
                                 Course::ResourceMap resources);

private:
    std::shared_ptr<ObjectManager> _objM;
    std::vector<std::shared_ptr<Player>> _playerList;
    unsigned _currentPlayer;
};

#endif // GAMEEVENTHANDLER_HH
