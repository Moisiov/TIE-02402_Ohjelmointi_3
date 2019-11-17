#include "gameeventhandler.hh"
#include "player.hh"
#include "buildings/hq.hh"
#include "workers/scout.hh"
#include "workers/worker.hh"
#include <math.h>

GameEventHandler::GameEventHandler():
    _objM(nullptr),
    _GEHandler(nullptr),
    _UI(nullptr),
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

void GameEventHandler::setMapWindow(std::shared_ptr<MapWindow> UI)
{
    _UI = UI;
}

void GameEventHandler::initializeGame(std::vector<std::string> playerNames,
                                      std::vector<PlayerColor> playerColors,
                                      unsigned map_x, unsigned map_y)
{
    for (unsigned i = 0; i < playerNames.size(); ++i) {
        std::shared_ptr<Player> player = std::make_shared<Player>(playerNames[i], playerColors[i]);
        _playerList.push_back(player);
    }

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

    for (unsigned i = 0; i < _playerList.size(); ++i) {
        _playerList[i]->setHQCoord(startPosition[i]);
        _objM->getTile(startPosition[i])->setOwner(_playerList[i]);

        _objM->constructBuilding("HeadQuarters", startPosition[i], _playerList[i]);

        Course::Coordinate scoutCoord = startPosition[i] + Course::Coordinate(0,1);
        _objM->constructUnit("Scout", scoutCoord, _playerList[i]);

        Course::Coordinate workerCoord = startPosition[i] + Course::Coordinate(0,-1);
        _objM->constructUnit("Worker", workerCoord, _playerList[i]);

        qDebug() << QString::fromStdString(_playerList[i]->getName()) << "initialization success!";
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

unsigned GameEventHandler::currentTurn()
{
    return _currentPlayer;
}

std::shared_ptr<Player> GameEventHandler::currentPlayer()
{
    return _playerList[_currentPlayer];
}

void GameEventHandler::endTurn()
{
    _currentPlayer += 1;
    if (_currentPlayer >= _playerList.size()) {
        _currentPlayer = 0;
    }

    _objM->restoreMoves(_playerList[_currentPlayer]);
    _objM->generateResources(_playerList[_currentPlayer]);
}

bool GameEventHandler::constructBuilding(std::string type, Course::Coordinate location)
{
    // TODO!!
    return true;
}

bool GameEventHandler::upgradeBuilding(std::shared_ptr<Course::BuildingBase> building)
{
    // TODO!!
    return true;
}

void GameEventHandler::sellBuilding(std::shared_ptr<Course::BuildingBase> building)
{
    // TODO!!
    return;
}

bool GameEventHandler::constructUnit(std::string type)
{
    // TODO!!
    return true;
}

bool GameEventHandler::moveUnit(std::shared_ptr<Course::WorkerBase> unit, Course::Coordinate destination)
{
    // TODO!!
    return true;
}
