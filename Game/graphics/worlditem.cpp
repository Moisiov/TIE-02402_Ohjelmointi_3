#include "worlditem.h"

#include <QDebug>

std::map<std::string, QColor> WorldItem::c_mapcolors = {{"Forest", QColor(20, 100, 20)},
                                                        {"Grassland", QColor(20, 230, 30)},
                                                        {"Sand", QColor(235, 200, 115)},
                                                        {"Stone", QColor(100, 100, 100)},
                                                        {"Swamp", QColor(90, 90, 30)},
                                                        {"Water", QColor(0, 170, 255)},
                                                       };

WorldItem::WorldItem(const std::shared_ptr<Course::GameObject> &obj, int size ):
    m_gameobject(obj), m_scenelocation(m_gameobject->getCoordinatePtr()->asQpoint()), m_size(size)
{
    addNewColor(m_gameobject->getType());
}

QRectF WorldItem::boundingRect() const
{
    return QRectF(m_scenelocation * m_size, m_scenelocation * m_size + QPoint(m_size, m_size));
}

void WorldItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED( option ); Q_UNUSED( widget );
    painter->setBrush(QBrush(c_mapcolors.at(m_gameobject->getType())));
    if ( m_gameobject->getType() == "" ){
        // Draw different types in different shapes
    }
    painter->drawRect(boundingRect());
}

const std::shared_ptr<Course::GameObject> &WorldItem::getBoundObject()
{
    return m_gameobject;
}

void WorldItem::updateLoc()
{
    if ( !m_gameobject ){
        delete this;
    } else {
        update(boundingRect()); // Test if necessary
        m_scenelocation = m_gameobject->getCoordinate().asQpoint();
    }
}

bool WorldItem::isSameObj(std::shared_ptr<Course::GameObject> obj)
{
    return obj == m_gameobject;
}

int WorldItem::getSize() const
{
    return m_size;
}

void WorldItem::setSize(int size)
{
    if ( size > 0 && size <= 500 ){
        m_size = size;
    }
}

void WorldItem::addNewColor(std::string type)
{
    qDebug() << "WorldItem::addNewColor() Type: " << type.c_str();
    if ( c_mapcolors.find(type) == c_mapcolors.end() ){
        std::size_t hash = std::hash<std::string>{}(type);
        c_mapcolors.insert({type, QColor((hash & 0xFF0000) >> 16, (hash & 0x00FF00 ) >> 8, (hash & 0x0000FF))});

    }
}
