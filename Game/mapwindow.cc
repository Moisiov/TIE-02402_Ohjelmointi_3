#include "mapwindow.hh"
#include "ui_mapwindow.h"

#include <math.h>

// These are for testing purposes
#include "core/worldgenerator.h"

#include "tiles/forest.h"
#include "tiles/grassland.h"
#include "tiles/sand.hh"
#include "tiles/stone.hh"
#include "tiles/swamp.hh"
#include "tiles/water.hh"

MapWindow::MapWindow(QWidget *parent,
                     std::shared_ptr<GameEventHandler> handler,
                     std::shared_ptr<ObjectManager> objManager):
    QMainWindow(parent),
    m_ui(new Ui::MapWindow),
    m_GEHandler(handler),
    m_objM(objManager),
    m_worldScene(new WorldScene(this)),
    m_readyToLaunch(false),
    m_playerList({}),
    m_currentPlayer(0),
    m_map_x(0),
    m_map_y(0)
{
    m_ui->setupUi(this);
    setupMenuConnections();
    m_ui->menuBrowser->setCurrentWidget(m_ui->mainMenu);

    m_objM->setScene(m_worldScene);

    WorldScene* sgs_rawptr = m_worldScene.get();

    // m_ui->graphicsView->height();
    // m_ui->graphicsView->width();

    m_ui->graphicsView->setScene(dynamic_cast<QGraphicsScene*>(sgs_rawptr));
    m_ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    // QTransform transform;
    // transform.rotate(45, Qt::XAxis);
    // m_ui->graphicsView->setTransform(transform);
    // m_ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorViewCenter);

    StartDialog dialog(this);
    connect(&dialog, &StartDialog::sendParameters,
                     this, &MapWindow::getParameters);
    connect(&dialog, &StartDialog::accepted,
            [=](){ m_readyToLaunch = true; });

    dialog.exec();
}

MapWindow::~MapWindow()
{
    delete m_ui;
}

bool MapWindow::isReadyToLaunch()
{
    return m_readyToLaunch;
}

void MapWindow::setSize(int width, int height)
{
    m_worldScene->setSize(width, height);
}

void MapWindow::setScale(int scale)
{
    m_worldScene->setScale(scale);
}

void MapWindow::resize()
{
    m_worldScene->resize();
}

void MapWindow::updateItem(std::shared_ptr<Course::GameObject> obj)
{
    m_worldScene->updateItem(obj);
}

void MapWindow::getParameters(std::vector<std::string> playerList, std::vector<PlayerColor> colorList, unsigned map_x, unsigned map_y)
{
    for (unsigned i = 0; i < playerList.size(); ++i) {
        std::string name = playerList[i];
        PlayerColor color = colorList[i];
        std::shared_ptr<Player> player = std::make_shared<Player>(name, color);
        m_playerList.push_back(player);
    }

    m_map_x = map_x;
    m_map_y = map_y;

    // Set map size to object manager according to the given values
    m_objM->setMapSize(map_x, map_y);

    // Testing the world generator
    Course::WorldGenerator::getInstance().addConstructor<Course::Forest>(2);
    Course::WorldGenerator::getInstance().addConstructor<Course::Grassland>(4);
    Course::WorldGenerator::getInstance().addConstructor<Sand>(4);
    Course::WorldGenerator::getInstance().addConstructor<Stone>(1);
    Course::WorldGenerator::getInstance().addConstructor<Swamp>(2);
    Course::WorldGenerator::getInstance().addConstructor<Water>(1);
    Course::WorldGenerator::getInstance().generateMap(map_x, map_y, 1, m_objM, m_GEHandler);

    m_objM->drawMap();

    m_GEHandler->initializeGame(m_playerList, map_x, map_y);
}

void MapWindow::objectSelected(std::shared_ptr<Course::GameObject> obj)
{
    std::string objType = obj->getType();
    m_ui->textBrowser_2->setText(objType.c_str());
    m_ui->menuBrowser->setCurrentWidget(m_ui->tileMenu);
}

void MapWindow::removeItem(std::shared_ptr<Course::GameObject> obj)
{
    m_worldScene->removeItem(obj);
}

void MapWindow::drawItem( std::shared_ptr<Course::GameObject> obj)
{
    m_worldScene->drawItem(obj);
}

void MapWindow::selectMainMenu()
{
    m_ui->menuBrowser->setCurrentWidget(m_ui->mainMenu);
}

void MapWindow::endTurn()
{
    // Call GameEventHandlers end turn function here
    qDebug() << "MapWindow::endTurn()";
}

void MapWindow::setupMenuConnections()
{
    connect(m_ui->menuBtn, &QPushButton::clicked, this, &MapWindow::selectMainMenu);
    connect(m_ui->endTurnBtn, &QPushButton::clicked, this, &MapWindow::endTurn);
    connect(m_worldScene.get(), &WorldScene::objectClicked, this, &MapWindow::objectSelected);
}
