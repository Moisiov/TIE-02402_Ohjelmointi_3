#ifndef MAPWINDOW_HH
#define MAPWINDOW_HH

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

#include <map>

#include "handlers/gameeventhandler.hh"
#include "handlers/objectmanager.hh"
#include "graphics/worldscene.h"
#include "graphics/worlditem.h"
#include "startdialog.hh"
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
    void resize();

    void drawItem( std::shared_ptr<Course::GameObject> obj);
    void removeItem( std::shared_ptr<Course::GameObject> obj);
    void updateItem( std::shared_ptr<Course::GameObject> obj);

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

private:
    Ui::MapWindow* m_ui;
    std::shared_ptr<GameEventHandler> m_GEHandler;
    std::shared_ptr<ObjectManager> m_objM;
    std::shared_ptr<WorldScene> m_worldScene;
    bool m_readyToLaunch; // default False until StartDialog emits Accepted
    std::vector<std::shared_ptr<Player>> m_playerList; // constructed with StartDialog parameters
    unsigned m_currentPlayer; // starts with 0
    unsigned m_map_x; // Filled in by StartDialog parameters
    unsigned m_map_y; // Filled in by StartDialog parameters
};

#endif // MapWINDOW_HH

