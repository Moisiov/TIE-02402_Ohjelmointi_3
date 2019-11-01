#include "mapwindow.hh"
#include "ui_mapwindow.h"

#include "graphics/worlditem.h"
#include "startdialog.hh"

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
                     std::shared_ptr<Course::iGameEventHandler> handler,
                     std::shared_ptr<ObjectManager> objManager):
    QMainWindow(parent),
    m_ui(new Ui::MapWindow),
    m_GEHandler(handler),
    m_objM(objManager),
    m_worldScene(new WorldScene(this))
{
    m_ui->setupUi(this);

    WorldScene* sgs_rawptr = m_worldScene.get();

    m_ui->graphicsView->setScene(dynamic_cast<QGraphicsScene*>(sgs_rawptr));

    // Testing the world generator
    Course::WorldGenerator::getInstance().addConstructor<Course::Forest>(2);
    Course::WorldGenerator::getInstance().addConstructor<Course::Grassland>(4);
    Course::WorldGenerator::getInstance().addConstructor<Sand>(4);
    Course::WorldGenerator::getInstance().addConstructor<Stone>(1);
    Course::WorldGenerator::getInstance().addConstructor<Swamp>(2);
    Course::WorldGenerator::getInstance().addConstructor<Water>(1);
    Course::WorldGenerator::getInstance().generateMap(10, 10, 1, m_objM, m_GEHandler);

    m_objM->drawMap(m_worldScene);

    StartDialog dialog(this);
    dialog.exec();
}

MapWindow::~MapWindow()
{
    delete m_ui;
}

void MapWindow::setGEHandler(
        std::shared_ptr<Course::iGameEventHandler> nHandler)
{
    m_GEHandler = nHandler;
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

void MapWindow::removeItem(std::shared_ptr<Course::GameObject> obj)
{
    m_worldScene->removeItem(obj);
}

void MapWindow::drawItem( std::shared_ptr<Course::GameObject> obj)
{
    m_worldScene->drawItem(obj);
}
