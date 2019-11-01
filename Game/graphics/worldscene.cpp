#include "worldscene.h"
#include "worlditem.h"

#include <QEvent>
#include <QGraphicsSceneMouseEvent>

#include <math.h>

WorldScene::WorldScene(QWidget* parent,
                                 int width,
                                 int height,
                                 int scale):
    QGraphicsScene(parent),
    w_mapBoundRect(nullptr),
    w_width(100),
    w_height(100),
    w_scale(50),
    w_mouse_right_pressed(false),
    w_x(0),
    w_y(0)
{
    setSize(width, height);
    setScale(scale);
}

void WorldScene::setSize(int width, int height)
{
    if ( width >= SCENE_WIDTH_LIMITS.first && width <= SCENE_WIDTH_LIMITS.second )
    {
        w_width = width;
    }
    if ( height >= SCENE_HEIGHT_LIMITS.first && height <= SCENE_HEIGHT_LIMITS.second )
    {
        w_height = height;
    }
    resize();
}

void WorldScene::setScale(int scale)
{
    if ( scale >= SCENE_SCALE_LIMITS.first && scale <= SCENE_SCALE_LIMITS.second )
    {
        w_scale = scale;
    }
    resize();
}

void WorldScene::resize()
{
    if ( w_mapBoundRect != nullptr ){
        QGraphicsScene::removeItem(w_mapBoundRect);
    }

    // Calculates rect with middle at (0,0).
    // Basically left upper corner coords and then width and height
    // QRect rect = QRect( m_width * m_scale / - 2, m_height * m_scale / -2,
    //                    m_width * m_scale - 1, m_height * m_scale - 1 );

    // Set upper left coordinate to (w_x, w_y)
    QRect rect = QRect( w_x, w_y, w_width * w_scale - 1, w_height * w_scale - 1 );

    addRect(rect, QPen(Qt::black));
    setSceneRect(rect);
    w_mapBoundRect = itemAt(rect.topLeft(), QTransform());

    // Draw on the bottom of all items
    w_mapBoundRect->setZValue(-1);
}

int WorldScene::getScale() const
{
    return w_scale;
}

std::pair<int, int> WorldScene::getSize() const
{
    return {w_width, w_height};
}

void WorldScene::updateItem(std::shared_ptr<Course::GameObject> obj)
{
    QList<QGraphicsItem*> items_list = items();
    if ( items_list.size() == 1 ){
        qDebug() << "Nothing to update.";
    } else {
        for ( auto item : items_list ){
            WorldItem* mapItem = static_cast<WorldItem*>(item);
            if (mapItem->isSameObj(obj)){
                mapItem->updateLoc();
            }
        }
    }
}

bool WorldScene::event(QEvent *event)
{
    if(event->type() == QEvent::GraphicsSceneMousePress)
    {
        QGraphicsSceneMouseEvent* mouse_event =
                dynamic_cast<QGraphicsSceneMouseEvent*>(event);

        if (mouse_event->button() == 1) {
            if ( sceneRect().contains(mouse_event->scenePos())){

                QPointF point = mouse_event->scenePos() / w_scale;

                point.rx() = floor(point.rx());
                point.ry() = floor(point.ry());
                qDebug() << "Click x: " << point.rx();
                qDebug() << "Click y: " << point.ry();

                QGraphicsItem* pressed = itemAt(point * w_scale, QTransform());

                if ( pressed == w_mapBoundRect ){
                    qDebug() << "Click on map area.";
                } else if (pressed != nullptr){
                    qDebug() << "ObjID: " <<
                                static_cast<WorldItem*>(pressed)
                                ->getBoundObject()->ID  << " pressed.";
                    return true;
                }

            }
        }

        if (mouse_event->button() == 2) {
            w_mouse_right_pressed = true;
        }
    }

    if(event->type() == QEvent::GraphicsSceneMouseRelease) {

        QGraphicsSceneMouseEvent* mouse_event =
                dynamic_cast<QGraphicsSceneMouseEvent*>(event);

        if (mouse_event->button() == 2) {
            w_mouse_right_pressed = false;
        }
    }

    if(event->type() == QEvent::GraphicsSceneMouseMove) {
        QGraphicsSceneMouseEvent* mouse_event =
                dynamic_cast<QGraphicsSceneMouseEvent*>(event);

        if (w_mouse_right_pressed == true) {
            QPoint lastPos = mouse_event->lastScreenPos();
            QPoint currentPos = mouse_event->screenPos();

            moveScene(currentPos.x()-lastPos.x(), currentPos.y()-lastPos.y());
        }
    }

    return false;
}


void WorldScene::removeItem(std::shared_ptr<Course::GameObject> obj)
{
    QList<QGraphicsItem*> items_list = items(obj->getCoordinate().asQpoint());
    if ( items_list.size() == 1 ){
        qDebug() << "Nothing to be removed at the location pointed by given obj.";
    } else {
        for ( auto item : items_list ){
            WorldItem* mapitem = static_cast<WorldItem*>(item);
            if ( mapitem->isSameObj(obj) ){
                delete mapitem;
            }
        }
    }
}

void WorldScene::drawItem( std::shared_ptr<Course::GameObject> obj)
{
    WorldItem* nItem = new WorldItem(obj, w_scale);
    addItem(nItem);
}

void WorldScene::moveScene(int x, int y)
{
    w_x -= x;
    w_y -= y;

    qDebug() << "x: " << w_x;
    qDebug() << "y: " << w_y;

    /*if (w_x < 0) {
        w_x = 0;
    }
    if (w_y < 0) {
        w_y = 0;
    }

    if (w_x > w_width) {
        w_x = w_width;
    }
    if (w_y > w_height) {
        w_y = w_height;
    }*/

    resize();
}
