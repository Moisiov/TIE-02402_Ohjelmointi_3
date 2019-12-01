#ifndef MAPWINDOW_HH
#define MAPWINDOW_HH

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QDialog>

#include <map>

#include "handlers/gameeventhandler.hh"
#include "handlers/objectmanager.hh"
#include "graphics/gameview.h"
#include "graphics/worldscene.h"
#include "graphics/worlditem.h"
#include "startdialog.hh"
#include "instructiondialog.h"
#include "player.hh"

namespace Ui {
class MapWindow;
}

/**
 * @brief The MapWindow class is the graphical interface for playing the game.
 */
class MapWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MapWindow constructor requires all parameters to be filled in
     * @param parent can be left as nullptr
     * @param GEHandler pointer to the GameEventHandler class
     * @param objManager pointer to the ObjectManager class
     */
    explicit MapWindow(QWidget *parent,
                       std::shared_ptr<GameEventHandler> GEHandler,
                       std::shared_ptr<ObjectManager> objManager
                       );
    ~MapWindow();

    /**
     * @brief isReadyToLaunch is needed by main.cc to test if player chose to cancel
     * the game initialization during StartDialog
     * @return True for ready
     */
    bool isReadyToLaunch();

    void setSize(int width, int height);
    void setScale(int scale);

    void drawItem( std::shared_ptr<Course::GameObject> obj);
    void removeItem( std::shared_ptr<Course::GameObject> obj);
    void updateItem( std::shared_ptr<Course::GameObject> obj);

    /**
     * @brief sendWarning displays information to player from failed commands
     * @param message
     */
    void sendWarning(std::string message);

    /**
     * @brief closeGame quits the game after the game is won
     */
    void closeGame();

public slots:
    /**
     * @brief getParameters is connected to StartDialogs signal to pass on start parameters
     * @param playerList The names of each player (in order)
     * @param colorList The colors of each player (in order)
     * @param map_x The width of the map
     * @param map_y The height of the map
     */
    void getParameters(std::vector<std::string> playerList,
                       std::vector<PlayerColor> colorList,
                       unsigned map_x,
                       unsigned map_y);

    /**
     * @brief objectSelected gets the signal from WorldScene when
     * an object on the screen is clicked.
     * @param obj is the clicked object.
     */
    void objectSelected(std::shared_ptr<Course::GameObject> obj);

    /**
     * @brief updatePlayerInfo makes sure that players name and resources info
     * is shown correctly
     */
    void updatePlayerInfo();

    /**
     * @brief scrollToCoordinate scrolls the game view to given coordinate
     * @param coordinate is the target coordinate
     */
    void scrollToCoordinate(Course::Coordinate coordinate);

    /**
     * @brief help slot for helpBtn click
     */
    void help();

private slots:
    /**
     * @brief selectMainMenu slot for menuBtn click.
     * Changes currently shown menu page to main menu.
     */
    void selectMainMenu();

    /**
     * @brief selectBuildingMenu changes menu view to building/build menu.
     */
    void selectBuildingMenu();

    /**
     * @brief buildAction is called when an building is selected in build menu
     * @param buildingType is the type of the building
     */
    void buildAction(std::string buildingType);

    /**
     * @brief selectWorkerMenu changes menu view to worker menu.
     */
    void selectWorkerMenu(unsigned workerIndex);

    /**
     * @brief selectUpgrade slot for upgradeBtn click
     */
    void selectUpgrade();

    /**
     * @brief selectSell slot for sellBtn click
     */
    void selectSell();

    /**
     * @brief selectMove for unit moving action
     */
    void selectMove();

    /**
     * @brief endTurn slot for endTurnBtn click.
     */
    void endTurn();

    /**
     * @brief constructUnit slot for constructUnitBtn click.
     * @param unit selected unit (0 = worker, 1 = scout, 2 = teekkari)
     */
    void constructUnit(int unit);

    /**
     * @brief selectSpecialize slot for upgradeUnitBtn click.
     */
    void selectSpecialize();

    /**
     * @brief specializeUnit is called when unit specialization is selected.
     * @param unitType new unit type
     */
    void specializeUnit(std::string unitType);

    /**
     * @brief highlightCapturedArea slot for capturedAreaBtn click
     */
    void highlightCapturedArea();

    /**
     * @brief highlightBuildingsAndWorkers slot for buildingsWorkersBtn click
     */
    void highlightBuildingsAndWorkers();

private:
    Ui::MapWindow* m_ui;
    std::shared_ptr<GameEventHandler> m_GEHandler;
    std::shared_ptr<ObjectManager> m_objM;
    std::shared_ptr<WorldScene> m_worldScene;
    bool m_readyToLaunch; // default False until StartDialog emits Accepted
    unsigned m_map_x; // Filled in by StartDialog parameters
    unsigned m_map_y; // Filled in by StartDialog parameters
    std::shared_ptr<Player> m_currentPlayer;
    std::shared_ptr<ExtendedTileBase> m_selectedTile;
    std::shared_ptr<UpgradeableBuilding> m_selectedBuilding;
    std::shared_ptr<UnitBase> m_selectedWorker;
    bool m_movingUnit;

    /**
     * @brief setupMenuConnections connects slots and signals in menu
     */
    void setupMenuConnections();

    /**
     * @brief generateResourceCostTooltip creates a string containing build/upgrade cost
     * @param objType string
     * @param tier int, building tier - default 0
     * @param sell set true for sell value - default false
     * @return string containing build/upgrade cost
     */
    std::string generateResourceCostTooltip(std::string objType, unsigned tier = 0, bool sell = false);

    /**
     * @brief generateProductionInfo generates production info of selected tile as text
     * @return production info
     */
    std::string generateProductionInfo();

    /**
     * @brief getCampusProgressText
     * @return returns campus progress as text (for example 20/100)
     */
    std::string getCampusProgressText();
};

#endif // MapWINDOW_HH

