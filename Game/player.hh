#ifndef PLAYER_HH
#define PLAYER_HH

#include "core/playerbase.h"
#include "core/basicresources.h"

enum PlayerColor { RED, BLUE, GREEN, ORANGE, PURPLE, CYAN };

class Player: public Course::PlayerBase
{
public:
    Player() = delete;

    Player(const std::string& name,
           PlayerColor color,
           const std::vector<std::shared_ptr<Course::GameObject>> objects = {});

    Player(const std::string& name,
           PlayerColor color,
           const Course::ResourceMap& startingResources,
           const std::vector<std::shared_ptr<Course::GameObject>> objects = {});

    ~Player() = default;

    Course::ResourceMap getResources();

    PlayerColor getColor();

    bool canAfford(Course::ResourceMap cost);

    bool modifyResource(Course::BasicResource resource, int amount);

    bool modifyResources(Course::ResourceMap resources);

private:
    Course::ResourceMap _resources;
    PlayerColor _color;
};

#endif // PLAYER_HH
