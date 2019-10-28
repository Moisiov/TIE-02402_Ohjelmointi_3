#ifndef GAMEEVENTHANDLER_HH
#define GAMEEVENTHANDLER_HH

#include "interfaces/igameeventhandler.h"

class GameEventHandler: public Course::iGameEventHandler
{
public:
    GameEventHandler();
    ~GameEventHandler() = default;

    // Finish this once ObjectManager class is defined
    // void giveObjectManager(std::shared_ptr<ObjectManager> objM);

    virtual bool modifyResource(std::shared_ptr<Course::PlayerBase> player,
                                Course::BasicResource resource,
                                int amount);

    virtual bool modifyResources(std::shared_ptr<Course::PlayerBase> player,
                                 Course::ResourceMap resources);
};

#endif // GAMEEVENTHANDLER_HH
