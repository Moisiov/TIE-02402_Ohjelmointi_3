#include "player.hh"

Player::Player(const std::string &name,
               const std::vector<std::shared_ptr<Course::GameObject> > objects):
    Course::PlayerBase(name, objects), _resources({})
{

}

Player::Player(const std::string &name,
               const Course::ResourceMap &startingResources,
               const std::vector<std::shared_ptr<Course::GameObject> > objects):
    Course::PlayerBase(name, objects), _resources(startingResources)
{

}

Course::ResourceMap Player::getResources()
{
    return _resources;
}

bool Player::canAfford(Course::ResourceMap cost)
{
    return true;
}

bool Player::modifyResource(Course::BasicResource resource, int amount)
{
    return true;
}

bool Player::modifyResources(Course::ResourceMap resources)
{
    return true;
}
