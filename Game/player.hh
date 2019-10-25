#ifndef PLAYER_HH
#define PLAYER_HH

#include "core/playerbase.h"
#include "core/basicresources.h"

class Player: public Course::PlayerBase
{
public:
    Player() = delete;

    Player(const std::string& name,
           const std::vector<std::shared_ptr<Course::GameObject>> objects = {});

    Player(const std::string& name,
           const Course::ResourceMap& startingResources,
           const std::vector<std::shared_ptr<Course::GameObject>> objects = {});

    ~Player() = default;

    Course::ResourceMap getResources();

    bool canAfford(Course::ResourceMap cost);

    bool modifyResource(std::shared_ptr<Course::PlayerBase> player,
                                    Course::BasicResource resource,
                                    int amount);
    bool modifyResources(std::shared_ptr<Course::PlayerBase> player,
                                     Course::ResourceMap resources);

private:
    Course::ResourceMap _resources;
};

#endif // PLAYER_HH
