#ifndef GAMEEVENTHANDLER_HH
#define GAMEEVENTHANDLER_HH

#include "interfaces/igameeventhandler.h"
#include "objectmanager.hh"

class GameEventHandler: public Course::iGameEventHandler
{
public:
    GameEventHandler();
    ~GameEventHandler() = default;

    void setObjectManager(std::shared_ptr<ObjectManager> objM);

    virtual bool modifyResource(std::shared_ptr<Course::PlayerBase> player,
                                Course::BasicResource resource,
                                int amount);

    virtual bool modifyResources(std::shared_ptr<Course::PlayerBase> player,
                                 Course::ResourceMap resources);

private:
    std::shared_ptr<ObjectManager> _objM;
};

#endif // GAMEEVENTHANDLER_HH
