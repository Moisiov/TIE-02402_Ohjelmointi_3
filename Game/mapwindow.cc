#include "mapwindow.hh"
#include "ui_mapwindow.h"

#include <math.h>

#include "core/worldgenerator.h"
#include "tiles/forest.h"
#include "tiles/grassland.h"
#include "tiles/sand.hh"
#include "tiles/stone.hh"
#include "tiles/swamp.hh"
#include "tiles/water.hh"

#include "exceptions/illegalaction.h"
#include "exceptions/graphicsexception.h"

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
    m_selectedWorker(nullptr),
    m_movingUnit(false)
{
    m_ui->setupUi(this);
    setWindowTitle("The Quest of TIE-02402: Impossible project");
    setupMenuConnections();

    QFile stylesFile(":/qss/stylesheet.qss");
    stylesFile.open(QFile::ReadOnly);
    QString stylesheet = QLatin1String(stylesFile.readAll());
    setStyleSheet(stylesheet);

    m_objM->setScene(m_worldScene);
    WorldScene* sgs_rawptr = m_worldScene.get();

    m_ui->graphicsView->setScene(dynamic_cast<QGraphicsScene*>(sgs_rawptr));
    m_ui->graphicsView->setRenderHint(QPainter::Antialiasing);

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

void MapWindow::updateItem(std::shared_ptr<Course::GameObject> obj)
{
    try
    {
        m_worldScene->updateItem(obj);
    }
    catch (GraphicsException e)
    {
        qDebug() << e.msg().c_str();
    }
}

void MapWindow::getParameters(std::vector<std::string> playerList, std::vector<PlayerColor> colorList, unsigned map_x, unsigned map_y)
{
    m_map_x = map_x;
    m_map_y = map_y;

    // Set map size to object manager according to the given values
    m_objM->setMapSize(map_x, map_y);

    m_worldScene->setSize(static_cast<int>(map_x),static_cast<int>(map_y));

    unsigned seed = static_cast<unsigned>(std::time(nullptr));

    // The world generator
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
    selectMainMenu();
    updatePlayerInfo();
    scrollToCoordinate(m_currentPlayer->getHQCoord());
}

void MapWindow::objectSelected(std::shared_ptr<Course::GameObject> obj)
{
    if (m_movingUnit)
    {
        try {
            m_GEHandler->moveUnit(m_selectedWorker, obj->getCoordinate());

            updateItem(m_selectedWorker);
            m_worldScene->highlightTile(obj->getCoordinate());
            m_ui->moveBtn->setDisabled(true);
            m_movingUnit = false;
            std::vector<std::shared_ptr<Course::WorkerBase>> workersOnTile = m_selectedTile->getWorkers();
            for (auto worker : workersOnTile)
            {
                updateItem(worker);
            }

        } catch (Course::IllegalAction e) {
            sendWarning(e.msg());
        }
    }

    else // Not m_movingUnit
    {
        m_selectedTile = std::dynamic_pointer_cast<ExtendedTileBase>(obj);

        // Check if clicked tile is owned by current player
        bool ownTile = m_selectedTile->getOwner() == m_currentPlayer;

        // Tile highlights
        m_worldScene->highlightTile(obj->getCoordinate());

        std::string objType = obj->getType();
        std::string infoText = objType;

        std::shared_ptr<Course::PlayerBase> owner = obj->getOwner();
        if (owner != nullptr) {
            //infoText += "\nOwner: " + owner->getName();
            infoText = m_selectedTile->description();
            infoText += "\n"+generateProductionInfo();
        }

        m_ui->tileBrowser->setText(infoText.c_str());

        // Check if tile has buildings or space for buildings
        // otherwise building button is disabled
        m_ui->buildingBtn->setText("Build");
        m_ui->buildingBtn->setDisabled(!(ownTile || m_GEHandler->scoutOnUnownedTile(m_selectedTile->getCoordinate())));
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
            m_ui->workerBtn1->setDisabled(!(workers.at(0)->getOwner() == m_currentPlayer));
            m_ui->workerBtn1->setText(workers.at(0)->getType().c_str());
        }
        if (workerCount > 1)
        {
            m_ui->workerBtn2->setDisabled(!(workers.at(1)->getOwner() == m_currentPlayer));
            m_ui->workerBtn2->setText(workers.at(1)->getType().c_str());
        }
        if (workerCount > 2)
        {
            m_ui->workerBtn3->setDisabled(!(workers.at(2)->getOwner() == m_currentPlayer));
            m_ui->workerBtn3->setText(workers.at(2)->getType().c_str());
        }

        m_ui->menuWidget->setCurrentWidget(m_ui->tileMenu);
        m_ui->graphicsView->update();
    }
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
    try
    {
        m_worldScene->removeItem(obj);
    }
    catch (GraphicsException e)
    {
        qDebug() << e.msg().c_str();
    }
}

void MapWindow::drawItem( std::shared_ptr<Course::GameObject> obj)
{
    m_worldScene->drawItem(obj);
}

void MapWindow::selectMainMenu()
{
    m_movingUnit = false;
    std::string infoText = m_currentPlayer->getName() + "\nCampus research progress: " + getCampusProgressText();
    m_ui->mainBrowser->setText(infoText.c_str());
    m_ui->menuWidget->setCurrentWidget(m_ui->mainMenu);
    m_ui->constructUnitBtn1->setToolTip(generateResourceCostTooltip("Worker").c_str());
    m_ui->constructUnitBtn2->setToolTip(generateResourceCostTooltip("Scout").c_str());
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
            button->setToolTip(generateResourceCostTooltip(buildables.at(i)).c_str());
            layout->addWidget(button);
            button->show();
        }

        buildButtons->setLayout(layout);
        m_ui->buildingsList->setWidget(buildButtons);
    }
    else
    {
        std::shared_ptr<UpgradeableBuilding> building =
                std::dynamic_pointer_cast<UpgradeableBuilding>(m_selectedTile->getBuildings().at(0));
        std::string type = building->getType();
        std::string infoText = building->description();
        //std::string infoText = building->getType() + "\n";
        //std::string buildingTier = std::to_string(building->getUpgradeTier());
        //infoText += "Building tier: " + buildingTier;
        m_ui->buildingBrowser->setText(infoText.c_str());
        m_selectedBuilding = building;

        // Disable sell button if building is HQ
        if(type == "HeadQuarters")
        {
            m_ui->sellBtn->setDisabled(true);
        }
        else
        {
            m_ui->sellBtn->setDisabled(false);
            m_ui->sellBtn->setToolTip(generateResourceCostTooltip(type, 0, true).c_str());
        }

        m_ui->upgradeBtn->setDisabled(!building->isUpgradeable());
        if (building->isUpgradeable())
        {
            m_ui->upgradeBtn->setToolTip(generateResourceCostTooltip(type, building->getUpgradeTier()+1).c_str());
        }

        m_ui->menuWidget->setCurrentWidget(m_ui->buildingMenu);
    }
}

void MapWindow::buildAction(std::string buildingType)
{
    try {
        m_GEHandler->constructBuilding(buildingType, m_selectedTile->getCoordinate());
        selectBuildingMenu();
        updatePlayerInfo();

    } catch (Course::IllegalAction e) {
        sendWarning(e.msg());
    }
}

void MapWindow::selectWorkerMenu(unsigned workerIndex)
{
    m_selectedWorker = std::dynamic_pointer_cast<UnitBase>
            (m_selectedTile->getWorkers().at(workerIndex));
    std::string infoText =m_selectedWorker->description();
    //std::string infoText = m_selectedWorker->getType();
    m_ui->workerBrowser->setText(infoText.c_str());

    // Disable move button if unit cannot move
    m_ui->moveBtn->setDisabled(!m_selectedWorker->canMove());

    // Disable specialize button if unit cannot be specialized
    m_ui->upgradeUnitBtn->setDisabled(m_selectedWorker->getType() != "Worker");

    m_ui->menuWidget->setCurrentWidget(m_ui->workerMenu);
}

void MapWindow::selectUpgrade()
{
    try {
        m_GEHandler->upgradeBuilding(m_selectedBuilding);
        updatePlayerInfo();
        selectBuildingMenu(); // Forces update of building info

    } catch (Course::IllegalAction e) {
        sendWarning(e.msg());
    }
}

void MapWindow::selectSell()
{
    try {
        removeItem(m_selectedBuilding);
        m_GEHandler->sellBuilding(m_selectedBuilding);
        updatePlayerInfo();
        selectMainMenu();

    } catch (Course::IllegalAction e) {
        sendWarning(e.msg());
    }

}

void MapWindow::selectMove()
{
    if (m_selectedWorker->canMove())
    {
        std::vector<Course::Coordinate> coords = m_selectedWorker->getCoordinate()
                .neighbours(static_cast<int>(m_selectedWorker->moveRange()));

        m_worldScene->highlightSelection(coords);
        m_movingUnit = true;
    }
}

void MapWindow::endTurn()
{
    m_movingUnit = false;
    m_GEHandler->endTurn();
    m_currentPlayer = m_GEHandler->currentPlayer();
    updatePlayerInfo();

    // Scroll to headquarter pos
    scrollToCoordinate(m_currentPlayer->getHQCoord());

    selectMainMenu();

    // Check if player won the game
    if (m_GEHandler->gameWon()) {
        std::string msg = m_currentPlayer->getName();
        msg += " finished research and wins the game!";
        sendWarning(msg);

        close();
    }
}

void MapWindow::constructUnit(int unit)
{
    std::string unitType = unit == 0 ? "Worker" : "Scout";

    try {
        m_GEHandler->constructUnit(unitType);
        updatePlayerInfo();

    } catch (Course::IllegalAction e) {
        sendWarning(e.msg());
    }

}

void MapWindow::selectSpecialize()
{
    m_ui->menuWidget->setCurrentWidget(m_ui->specializeMenu);

    // Add correct buttons to the specialization menu
    QWidget* specializeButtons = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->setAlignment(Qt::AlignTop);

    std::vector<std::string> specialTypes = SPECIALIZATIONS;
    for (unsigned i = 0; i < specialTypes.size(); ++i)
    {
        QPushButton* button = new QPushButton(this);
        connect(button, &QPushButton::clicked, this, [this, specialTypes, i] { specializeUnit(specialTypes.at(i)); });
        button->setText(specialTypes.at(i).c_str());
        button->setToolTip(generateResourceCostTooltip(specialTypes.at(i)).c_str());
        button->setFixedSize(QSize(201, 61));
        layout->addWidget(button);
        button->show();
    }

    specializeButtons->setLayout(layout);
    m_ui->specializationList->setWidget(specializeButtons);
}

void MapWindow::specializeUnit(std::string unitType)
{
    try {
        std::shared_ptr<Worker> unit = std::dynamic_pointer_cast<Worker>(m_selectedWorker);
        m_GEHandler->specializeUnit(unit, unitType);
        m_worldScene->updateItem(m_selectedWorker);
        // Return to worker menu
        std::string infoText = m_selectedWorker->getType();
        m_ui->workerBrowser->setText(infoText.c_str());

        // Disable move button if unit cannot move
        m_ui->moveBtn->setDisabled(!m_selectedWorker->canMove());

        // Disable specialize button if unit cannot be specialized
        m_ui->upgradeUnitBtn->setDisabled(m_selectedWorker->getType() != "Worker");

        m_ui->menuWidget->setCurrentWidget(m_ui->workerMenu);
        updatePlayerInfo();

    } catch (Course::IllegalAction e) {
        sendWarning(e.msg());
    }
}

void MapWindow::highlightCapturedArea()
{
    m_worldScene->highlightSelection(m_GEHandler->getCurrentPlayerZone());
}

void MapWindow::highlightBuildingsAndWorkers()
{
    std::vector<std::shared_ptr<UnitBase>> units = m_objM->getUnits();
    std::vector<std::shared_ptr<UpgradeableBuilding>> buildings = m_objM->getBuildings();

    std::vector<Course::Coordinate> coordinates = {};

    for (auto unit : units)
    {
        if(unit->getOwner() == m_currentPlayer)
        {
            coordinates.push_back(unit->getCoordinate());
        }
    }

    for (auto building : buildings)
    {
        if(building->getOwner() == m_currentPlayer)
        {
            coordinates.push_back(building->getCoordinate());
        }
    }

    m_worldScene->highlightSelection(coordinates);
}

void MapWindow::help()
{
    InstructionDialog instr(this);
    instr.exec();
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
    connect(m_ui->constructUnitBtn1, &QPushButton::clicked, [this]{ constructUnit(0); });
    connect(m_ui->constructUnitBtn2, &QPushButton::clicked, [this]{ constructUnit(1); });
    connect(m_ui->upgradeUnitBtn, &QPushButton::clicked, this, &MapWindow::selectSpecialize);
    connect(m_ui->capturedAreaBtn, &QPushButton::clicked, this, &MapWindow::highlightCapturedArea);
    connect(m_ui->helpBtn, &QPushButton::clicked, this, &MapWindow::help);
    connect(m_ui->buildingsWorkersBtn, &QPushButton::clicked, this, &MapWindow::highlightBuildingsAndWorkers);
}

std::string MapWindow::generateResourceCostTooltip(std::string objType, unsigned tier, bool sell)
{
    std::string costText = sell ? "Sell this building for\n" : "Cost\n";
    double multiplier = sell ? 0.5 : 1;
    Course::ResourceMap cost = {};

    if (BUILDING_BUILD_COSTS.find(objType) != BUILDING_BUILD_COSTS.end() && tier < 3) {
        cost = BUILDING_BUILD_COSTS.at(objType).at(tier);
    }
    else if (objType == "Worker")
    {
        costText = "Hire a worker at your HeadQuarters location.\nCost\n";
        cost = BASIC_WORKER_BUILD_COST;
    }
    else if (objType == "Scout")
    {
        costText = "Hire a scout at your HeadQuarters location.\nCost\n";
        cost = SCOUT_BUILD_COST;
    }
    else if (SPECIALIZATION_COST.find(objType) != SPECIALIZATION_COST.end())
    {
        costText = "Promote this worker to " + objType + ".\nCost\n";
        cost = SPECIALIZATION_COST.at(objType);
    }

    for (auto resource : cost)
    {
        int value = static_cast<int>(resource.second*multiplier);

        switch (resource.first)
        {
            case 1:
                costText += "Money: " + std::to_string(value) + "\n";
                break;
            case 2:
                costText += "Food: " + std::to_string(value) + "\n";
                break;
            case 3:
                costText += "Wood: " + std::to_string(value) + "\n";
                break;
            case 4:
                costText += "Stone: " + std::to_string(value) + "\n";
                break;
            case 5:
                costText += "Ore: " + std::to_string(value) + "\n";
                break;
            default:
                break;
        }
    }

    costText.erase(costText.find_last_not_of(" \n\r\t")+1);
    return costText;
}

std::string MapWindow::generateProductionInfo()
{
    std::string productionText = "Produces\n";

    Course::ResourceMap production = m_selectedTile->calculateProduction();

    int total = 0;

    for (auto resource : production)
    {
        int value = resource.second;
        if (value != 0) {
            total += value;

            switch (resource.first)
            {
                case 1:
                    productionText += "Money: " + std::to_string(value) + " / turn" + "\n";
                    break;
                case 2:
                    productionText += "Food: " + std::to_string(value) + " / turn" + "\n";
                    break;
                case 3:
                    productionText += "Wood: " + std::to_string(value) + " / turn" + "\n";
                    break;
                case 4:
                    productionText += "Stone: " + std::to_string(value) + " / turn" + "\n";
                    break;
                case 5:
                    productionText += "Ore: " + std::to_string(value) + " / turn" + "\n";
                    break;
                default:
                    break;
            }
        }

    }

    if (total == 0) {productionText = "Tile needs workers to produce resources.";}

    return productionText;
}

std::string MapWindow::getCampusProgressText()
{
    return std::to_string(m_objM->getCampusProgress(m_currentPlayer)) + "/100";
}
