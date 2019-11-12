#include "gameeventhandler.hh"
#include "player.hh"
#include "buildings/hq.hh"
#include <math.h>

GameEventHandler::GameEventHandler():
    _objM(nullptr),
    _GEHandler(nullptr),
    _playerList({}),
    _currentPlayer(0),
    _map_x(0),
    _map_y(0)
{

}

void GameEventHandler::setGEHandler(std::shared_ptr<GameEventHandler> GEHandler)
{
    _GEHandler = GEHandler;
}

void GameEventHandler::setObjectManager(std::shared_ptr<ObjectManager> objM)
{
    _objM = objM;
}

void GameEventHandler::initializeGame(std::vector<std::shared_ptr<Player>> playerList,
                                      unsigned map_x, unsigned map_y)
{
    _playerList = playerList;
    _map_x = map_x;
    _map_y = map_y;

    std::vector<Course::Coordinate> startPosition = {
        Course::Coordinate(0,0),
        Course::Coordinate(0,0),
        Course::Coordinate(0,0),
        Course::Coordinate(0,0),
        Course::Coordinate(0,0),
        Course::Coordinate(0,0)
    };

    int x_offset;
    if (map_x % 3 == 2) {
        x_offset = static_cast<int>((map_x - 14) / 3 + 1);
    } else {
        x_offset = static_cast<int>((map_x - 14) / 3);
    }

    // Player 1 coordinates
    startPosition[0].set_x(3);
    startPosition[0].set_y(static_cast<int>(map_y / 2));

    // Player 2 coordinates
    startPosition[1].set_x(static_cast<int>(map_x - 4));
    startPosition[1].set_y(static_cast<int>(map_y / 2));

    // Player 3 coordinates
    startPosition[2].set_x(x_offset + 3);
    startPosition[2].set_y(3);

    // Player 4 coordinates
    startPosition[3].set_x(static_cast<int>(map_x) - x_offset - 4);
    startPosition[3].set_y(static_cast<int>(map_y) - 4);

    // Player 5 coordinates
    startPosition[4].set_x(x_offset + 3);
    startPosition[4].set_y(static_cast<int>(map_y) - 4);

    // Player 6 coordinates
    startPosition[5].set_x(static_cast<int>(map_x) - x_offset - 4);
    startPosition[5].set_y(3);

    for (unsigned i = 0; i < playerList.size(); ++i) {
        playerList[i]->setHQCoord(startPosition[i]);

        // TODO: Initialize HQ, first worker and scout for each player

        std::shared_ptr<HQ> headquarter = std::make_shared<HQ>(_GEHandler, _objM, playerList[i]);
        headquarter->setCoordinate(startPosition[i]);
        headquarter->onBuildAction();
        qDebug() << "HQ Build success!";
    }
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
