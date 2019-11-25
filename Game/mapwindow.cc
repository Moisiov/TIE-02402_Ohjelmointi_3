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
    m_map_x(0),
    m_map_y(0),
    m_currentPlayer(nullptr),
    m_selectedTile(nullptr),
    m_selectedBuilding(nullptr),
    m_selectedWorker(nullptr)
{
    m_ui->setupUi(this);
    setupMenuConnections();
    m_ui->menuWidget->setCurrentWidget(m_ui->mainMenu);

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
    m_map_x = map_x;
    m_map_y = map_y;

    // Set map size to object manager according to the given values
    m_objM->setMapSize(map_x, map_y);

    m_worldScene->setSize(static_cast<int>(map_x),static_cast<int>(map_y));

    unsigned seed = static_cast<unsigned>(std::time(nullptr));

    // Testing the world generator
    Course::WorldGenerator::getInstance().addConstructor<Forest>(2);
    Course::WorldGenerator::getInstance().addConstructor<Grassland>(3);
    Course::WorldGenerator::getInstance().addConstructor<Sand>(1);
    Course::WorldGenerator::getInstance().addConstructor<Stone>(1);
    Course::WorldGenerator::getInstance().addConstructor<Swamp>(1);
    Course::WorldGenerator::getInstance().addConstructor<Water>(1);
    Course::WorldGenerator::getInstance().generateMap(map_x, map_y, seed, m_objM, m_GEHandler);

    m_objM->drawMap();

    m_GEHandler->initializeGame(playerList, colorList, map_x, map_y);
    m_currentPlayer = m_GEHandler->currentPlayer();
    updatePlayerInfo();
    scrollToCoordinate(m_currentPlayer->getHQCoord());
}

void MapWindow::objectSelected(std::shared_ptr<Course::GameObject> obj)
{
    // Tile highlights
    m_worldScene->highlightTile(obj->getCoordinate());

    m_selectedTile = std::dynamic_pointer_cast<ExtendedTileBase>(obj);

    std::string objType = obj->getType();
    std::string infoText = objType;

    Course::Coordinate coord = obj->getCoordinate();
    infoText += "\n(" + std::to_string(coord.x()) + "," + std::to_string(coord.y()) + ")";

    std::shared_ptr<Course::PlayerBase> owner = obj->getOwner();
    if (owner != nullptr) {
        infoText += "\nOwner: " + owner->getName();
    }

    m_ui->tileBrowser->setText(infoText.c_str());

    // Check if tile has buildings or space for buildings
    // otherwise building button is disabled
    m_ui->buildingBtn->setText("Build");
    m_ui->buildingBtn->setDisabled(false);
    if (m_selectedTile->getBuildingCount() > 0)
    {
        std::string buildingType = m_selectedTile->getBuildings().at(0)->getType();
        m_ui->buildingBtn->setText(buildingType.c_str());
    }
    else if (!m_selectedTile->hasSpaceForBuildings(1))
    {
        m_ui->buildingBtn->setDisabled(true);
    }

    // Check if tile has workers and set button text correctly
    unsigned workerCount = m_selectedTile->getWorkerCount();
    std::vector<std::shared_ptr<Course::WorkerBase>> workers = m_selectedTile->getWorkers();
    m_ui->workerBtn1->setDisabled(true);
    m_ui->workerBtn1->setText("-");
    m_ui->workerBtn2->setDisabled(true);
    m_ui->workerBtn2->setText("-");
    m_ui->workerBtn3->setDisabled(true);
    m_ui->workerBtn3->setText("-");

    if (workerCount > 0)
    {
        m_ui->workerBtn1->setDisabled(false);
        m_ui->workerBtn1->setText(workers.at(0)->getType().c_str());
    }
    if (workerCount > 1)
    {
        m_ui->workerBtn2->setDisabled(false);
        m_ui->workerBtn2->setText(workers.at(1)->getType().c_str());
    }
    if (workerCount > 2)
    {
        m_ui->workerBtn3->setDisabled(false);
        m_ui->workerBtn3->setText(workers.at(2)->getType().c_str());
    }

    m_ui->menuWidget->setCurrentWidget(m_ui->tileMenu);
    m_ui->graphicsView->update();
}

void MapWindow::updatePlayerInfo()
{
    Course::ResourceMap resources = m_currentPlayer->getResources();

    std::string infoText = m_currentPlayer->getName() + "       ";

    infoText += "Money: " + std::to_string(resources.at(Course::BasicResource::MONEY)) + ", ";
    infoText += "Food: " + std::to_string(resources.at(Course::BasicResource::FOOD)) + ", ";
    infoText += "Wood: " + std::to_string(resources.at(Course::BasicResource::WOOD)) + ", ";
    infoText += "Stone: " + std::to_string(resources.at(Course::BasicResource::STONE)) + ", ";
    infoText += "Ore: " + std::to_string(resources.at(Course::BasicResource::ORE));

    m_ui->infoBar->setText(infoText.c_str());
}

void MapWindow::scrollToCoordinate(Course::Coordinate coordinate)
{
    int scale = m_worldScene->getScale();
    m_ui->graphicsView->centerOn(coordinate.x()*scale+(scale/2), coordinate.y()*scale+(scale/2));
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
    m_ui->menuWidget->setCurrentWidget(m_ui->mainMenu);
    m_worldScene->clearHighlight();
}

void MapWindow::selectBuildingMenu()
{
    if (m_selectedTile->hasSpaceForBuildings(1))
    {
        m_ui->menuWidget->setCurrentWidget(m_ui->buildMenu);

        // Add correct buttons to the build menu
        QWidget* buildButtons = new QWidget();
        QVBoxLayout* layout = new QVBoxLayout();
        layout->setMargin(0);
        layout->setAlignment(Qt::AlignTop);

        std::vector<std::string> buildables = m_selectedTile->getBuildableBuildings();
        for (unsigned i = 0; i < buildables.size(); ++i)
        {
            QPushButton* button = new QPushButton(this);
            connect(button, &QPushButton::clicked, this, [this, buildables, i] { buildAction(buildables.at(i)); });
            button->setText(buildables.at(i).c_str());
            button->setFixedSize(QSize(201, 61));
            layout->addWidget(button);
            button->show();
        }

        buildButtons->setLayout(layout);
        m_ui->scrollArea->setWidget(buildButtons);
    }
    else
    {
        std::shared_ptr<UpgradeableBuilding> building =
                std::dynamic_pointer_cast<UpgradeableBuilding>(m_selectedTile->getBuildings().at(0));
        std::string infoText = building->getType();
        m_ui->buildingBrowser->setText(infoText.c_str());
        m_selectedBuilding = building;

        m_ui->menuWidget->setCurrentWidget(m_ui->buildingMenu);
    }
}

void MapWindow::buildAction(std::string buildingType)
{
    bool buildSuccess = m_GEHandler->constructBuilding(buildingType, m_selectedTile->getCoordinate());
    if (buildSuccess) {
        selectBuildingMenu();
        updatePlayerInfo();
    }
}

void MapWindow::selectWorkerMenu(unsigned workerIndex)
{
    m_selectedWorker = std::dynamic_pointer_cast<UnitBase>
            (m_selectedTile->getWorkers().at(workerIndex));
    std::string infoText = m_selectedWorker->getType();
    m_ui->workerBrowser->setText(infoText.c_str());

    // Disable move button if unit cannot move
    m_ui->moveBtn->setDisabled(!m_selectedWorker->canMove());

    m_ui->menuWidget->setCurrentWidget(m_ui->workerMenu);
}

void MapWindow::selectUpgrade()
{
    bool upgradeSuccess = m_GEHandler->upgradeBuilding(m_selectedBuilding);
    if (upgradeSuccess) {
        updatePlayerInfo();
    }
}

void MapWindow::selectSell()
{
    removeItem(m_selectedBuilding);
    m_GEHandler->sellBuilding(m_selectedBuilding);
    updatePlayerInfo();
}

void MapWindow::selectMove()
{
    if (m_selectedWorker->canMove())
    {
        std::vector<Course::Coordinate> coords = m_selectedWorker->getCoordinate()
                .neighbours(static_cast<int>(m_selectedWorker->moveRange()));

        m_worldScene->highlightSelection(coords);
    }
}

void MapWindow::endTurn()
{
    m_GEHandler->endTurn();
    m_currentPlayer = m_GEHandler->currentPlayer();
    updatePlayerInfo();

    // Scroll to headquarter pos
    scrollToCoordinate(m_currentPlayer->getHQCoord());

    selectMainMenu();
}

void MapWindow::sendWarning(std::string message)
{
    QMessageBox warning;
    warning.setText(QString::fromStdString(message));
    warning.exec();
    return;
}

void MapWindow::closeGame()
{
    close();
}

void MapWindow::setupMenuConnections()
{
    connect(m_ui->menuBtn, &QPushButton::clicked, this, &MapWindow::selectMainMenu);
    connect(m_ui->buildingBtn, &QPushButton::clicked, this, &MapWindow::selectBuildingMenu);
    connect(m_ui->workerBtn1, &QPushButton::clicked, this, [this]{ selectWorkerMenu(0); });
    connect(m_ui->workerBtn2, &QPushButton::clicked, this, [this]{ selectWorkerMenu(1); });
    connect(m_ui->workerBtn3, &QPushButton::clicked, this, [this]{ selectWorkerMenu(2); });
    connect(m_ui->endTurnBtn, &QPushButton::clicked, this, &MapWindow::endTurn);
    connect(m_ui->upgradeBtn, &QPushButton::clicked, this, &MapWindow::selectUpgrade);
    connect(m_ui->sellBtn, &QPushButton::clicked, this, &MapWindow::selectSell);
    connect(m_ui->moveBtn, &QPushButton::clicked, this, &MapWindow::selectMove);
    connect(m_worldScene.get(), &WorldScene::objectClicked, this, &MapWindow::objectSelected);
}
