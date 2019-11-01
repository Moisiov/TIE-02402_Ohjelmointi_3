#include "gameeventhandler.hh"
#include "player.hh"

GameEventHandler::GameEventHandler(): _objM(nullptr)
{

}

void GameEventHandler::setObjectManager(std::shared_ptr<ObjectManager> objM)
{
    _objM = objM;
}

void GameEventHandler::setPlayerList(std::vector<std::shared_ptr<Player> > playerList)
{
    _playerList = playerList;
}

bool GameEventHandler::modifyResource(
        std::shared_ptr<Course::PlayerBase> player,
        Course::BasicResource resource,
        int amount)
{
    std::shared_ptr<Player> player_ptr = std::dynamic_pointer_cast<Player> (player);

    return player_ptr->modifyResource(resource, amount);
}

bool GameEventHandler::modifyResources(
        std::shared_ptr<Course::PlayerBase> player,
        Course::ResourceMap resources)
{
    std::shared_ptr<Player> player_ptr = std::dynamic_pointer_cast<Player> (player);

    return player_ptr->modifyResources(resources);
}
