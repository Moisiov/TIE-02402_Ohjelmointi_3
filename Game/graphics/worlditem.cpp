#include "worlditem.h"
#include "player.hh"

#include <QDebug>
#include <QtWidgets>

std::map<std::string, QColor> WorldItem::c_mapcolors = {{"Forest", QColor(20, 100, 20)},
                                                        {"Grassland", QColor(20, 230, 30)},
                                                        {"Sand", QColor(235, 200, 115)},
                                                        {"Stone", QColor(100, 100, 100)},
                                                        {"Swamp", QColor(90, 90, 30)},
                                                        {"Water", QColor(0, 170, 255)}
                                                       };

WorldItem::WorldItem(const std::shared_ptr<Course::GameObject> &obj, int size ):
    w_gameobject(obj), w_scenelocation(w_gameobject->getCoordinatePtr()->asQpoint()), w_size(size)
{
    addNewColor(w_gameobject->getType());

    // Set cache mode to speed up rendering
    setCacheMode(WorldItem::DeviceCoordinateCache);
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

    painter->setBrush(QBrush(c_mapcolors.at(objType)));

    // get level of detail for zoomed rendering (lod = 1 no zoom, lod < 1 zoom out, lod > 1 zoom in)
    const qreal lod = option->levelOfDetailFromTransform(painter->worldTransform());

    if ( w_gameobject->getType() == "HeadQuarters" ){
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
        painter->drawEllipse(boundingRect());
    } else {
        painter->drawRect(boundingRect());
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
        update(boundingRect()); // Test if necessary
        w_scenelocation = w_gameobject->getCoordinate().asQpoint();
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

void WorldItem::addNewColor(std::string type)
{
    if ( c_mapcolors.find(type) == c_mapcolors.end() ){
        std::size_t hash = std::hash<std::string>{}(type);
        c_mapcolors.insert({type, QColor((hash & 0xFF0000) >> 16, (hash & 0x00FF00 ) >> 8, (hash & 0x0000FF))});

    }
}
