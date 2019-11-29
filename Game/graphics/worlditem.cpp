#include "worlditem.h"
#include "player.hh"

#include <QDebug>
#include <QtWidgets>
#include <QPixmap>
#include "basicinfo.hh"

std::map<std::string, QColor> WorldItem::c_mapcolors = {{"Forest", QColor(20, 100, 20)},
                                                        {"Grassland", QColor(20, 230, 30)},
                                                        {"Sand", QColor(235, 200, 115)},
                                                        {"Stone", QColor(100, 100, 100)},
                                                        {"Swamp", QColor(90, 90, 30)},
                                                        {"Water", QColor(0, 170, 255)}
                                                       };

std::map<std::string, QString> WorldItem::_pixmapUrls = {{"Grassland", ":/graphics/images/grassland.png"},
                                                         {"Sand", ":/graphics/images/sand.png"},
                                                         {"Forest", ":/graphics/images/forest.png"},
                                                         {"Swamp", ":/graphics/images/swamp.png"},
                                                         {"Stone", ":/graphics/images/stone.png"},
                                                         {"Water", ":/graphics/images/water.png"},
                                                         {"HeadQuarters", ":/graphics/images/headquarters.png"},
                                                         {"Campus", ":/graphics/images/campus.png"},
                                                         {"Fishery", ":/graphics/images/fishery.png"},
                                                         {"Outpost", ":/graphics/images/outpost.png"},
                                                         {"Mine", ":/graphics/images/mine.png"},
                                                         {"Sawmill", ":/graphics/images/sawmill.png"},
                                                         {"Farm", ":/graphics/images/farm.png"},
                                                         {"Worker", ":/graphics/images/worker.png"},
                                                         {"Scout", ":/graphics/images/scout.png"},
                                                         {"Teekkari", ":/graphics/images/teekkari.png"},
                                                         {"Farmer", ":/graphics/images/farmer.png"},
                                                         {"Lumberjack", ":/graphics/images/lumberjack.png"},
                                                         {"Miner", ":/graphics/images/miner.png"},
                                                         {"Merchant", ":/graphics/images/merchant.png"},
                                                         {"Market", ":/graphics/images/marketplace.png"}};

WorldItem::WorldItem(const std::shared_ptr<Course::GameObject> &obj, int size ):
    w_gameobject(obj), w_scenelocation(w_gameobject->getCoordinatePtr()->asQpoint()), w_size(size)
{
    addNewColor(w_gameobject->getType());

    // Set cache mode to speed up rendering
    setCacheMode(WorldItem::DeviceCoordinateCache);

    setZVal();
}

QRectF WorldItem::boundingRect() const
{
    return QRectF(w_scenelocation * w_size, w_scenelocation * w_size + QPoint(w_size, w_size));
}

void WorldItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED( option ); Q_UNUSED( widget );

    std::string objType = w_gameobject->getType();

    // if type doesn't exist in c_mapcolors, add new
    if (c_mapcolors.find(objType) == c_mapcolors.end())
    {
        addNewColor(objType);
    }

    // get level of detail for zoomed rendering (lod = 1 no zoom, lod < 1 zoom out, lod > 1 zoom in)
    // const qreal lod = option->levelOfDetailFromTransform(painter->worldTransform());

    try
    {
        QString url = _pixmapUrls.at(objType);
        QPixmap pic = QPixmap(url);
        pic.setDevicePixelRatio(100/w_size);
        QPoint offset = getImgOffset();
        painter->drawPixmap(w_scenelocation*w_size + offset, pic);
    }
    catch (...)
    {
        painter->setBrush(QBrush(c_mapcolors.at(objType)));
        painter->drawRect(boundingRect());
    }

    // Draw player marker if object is building or worker
    if (std::find(TILETYPES.begin(), TILETYPES.end(), objType) == TILETYPES.end())
    {
        drawPlayerMarker(painter);
    }
}

const std::shared_ptr<Course::GameObject> &WorldItem::getBoundObject()
{
    return w_gameobject;
}

void WorldItem::updateLoc()
{
    if ( !w_gameobject ){
        delete this;
    } else {
        prepareGeometryChange();
        w_scenelocation = w_gameobject->getCoordinate().asQpoint();
        update(boundingRect());
    }
}

bool WorldItem::isSameObj(std::shared_ptr<Course::GameObject> obj)
{
    return obj == w_gameobject;
}

int WorldItem::getSize() const
{
    return w_size;
}

void WorldItem::setSize(int size)
{
    if ( size > 0 && size <= 500 ){
        w_size = size;
    }
}

void WorldItem::drawPlayerMarker(QPainter *painter)
{
    std::shared_ptr<Player> player = std::dynamic_pointer_cast<Player>(w_gameobject->getOwner());
    PlayerColor playerColor = player->getColor();
    QColor color;

    // Get player color
    switch (playerColor) {
        case 0:
            color = QColor(Qt::blue);
            break;
        case 1:
            color = QColor(Qt::red);
            break;
        case 2:
            color = QColor(Qt::green);
            break;
        case 3:
            color = QColor(255, 100, 0);
            break;
        case 4:
            color = QColor(100, 0, 255);
            break;
        case 5:
            color = QColor(Qt::cyan);
            break;
        default:
            break;
    }

    painter->setBrush(QBrush(color));
    painter->setPen(color);
    painter->drawEllipse(QRectF(w_scenelocation * w_size + QPoint(w_size/20, w_size/20), w_scenelocation * w_size + QPoint(w_size/10, w_size/10)));
}

QPoint WorldItem::getImgOffset()
{
    QPoint offset = QPoint(0, 0);

    if (std::find(WORKERTYPES.begin(), WORKERTYPES.end(), w_gameobject->getType()) != WORKERTYPES.end())
    {
        QGraphicsItem* tileGraphics = scene()->items(w_scenelocation * w_size).last();
        std::shared_ptr<Course::TileBase> tile = std::dynamic_pointer_cast<Course::TileBase>
                (static_cast<WorldItem*>(tileGraphics)->getBoundObject());

        std::vector<std::shared_ptr<Course::WorkerBase>> workersOnTile = tile->getWorkers();

        int multiplier = 0;
        for(auto worker : workersOnTile)
        {
            if(worker == w_gameobject)
            {
                offset = QPoint(w_size*multiplier/3, 0);
            }

            multiplier++;
        }
    }

    return offset;
}

void WorldItem::setZVal()
{
    std::string type = w_gameobject->getType();

    if (std::find(BUILDINGTYPES.begin(), BUILDINGTYPES.end(), type) != BUILDINGTYPES.end())
    {
        setZValue(1);
    }
    else if (std::find(WORKERTYPES.begin(), WORKERTYPES.end(), type) != WORKERTYPES.end())
    {
        setZValue(3);
    }
}

void WorldItem::addNewColor(std::string type)
{
    if ( c_mapcolors.find(type) == c_mapcolors.end() ){
        std::size_t hash = std::hash<std::string>{}(type);
        c_mapcolors.insert({type, QColor((hash & 0xFF0000) >> 16, (hash & 0x00FF00 ) >> 8, (hash & 0x0000FF))});

    }
}
