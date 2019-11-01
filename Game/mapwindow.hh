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

class MapWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MapWindow(QWidget *parent,
                       std::shared_ptr<GameEventHandler> GEHandler,
                       std::shared_ptr<ObjectManager> objManager
                       );
    ~MapWindow();

    bool isReadyToLaunch();

    void setSize(int width, int height);
    void setScale(int scale);
    void resize();

    void drawItem( std::shared_ptr<Course::GameObject> obj);
    void removeItem( std::shared_ptr<Course::GameObject> obj);
    void updateItem( std::shared_ptr<Course::GameObject> obj);

public slots:
    void getParameters(std::vector<std::string> playerList,
                       std::vector<PlayerColor> colorList,
                       unsigned map_x,
                       unsigned map_y);

private:
    Ui::MapWindow* m_ui;
    std::shared_ptr<GameEventHandler> m_GEHandler = nullptr;
    std::shared_ptr<ObjectManager> m_objM = nullptr;
    std::shared_ptr<WorldScene> m_worldScene = nullptr;

    bool m_readyToLaunch;
    std::vector<std::shared_ptr<Player>> m_playerList;
    unsigned m_currentPlayer;
    unsigned m_map_x;
    unsigned m_map_y;
};

#endif // MapWINDOW_HH

