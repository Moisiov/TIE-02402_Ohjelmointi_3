#include "worldscene.h"
#include "worlditem.h"
#include "mapwindow.hh"

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
    w_selectedTile(nullptr)
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
    // Check if drag mode is on (right click fakes left click to allow dragging)
    if(views().at(0)->dragMode() != QGraphicsView::DragMode::ScrollHandDrag) {
        if(event->type() == QEvent::GraphicsSceneMousePress)
        {
            QGraphicsSceneMouseEvent* mouse_event =
                    dynamic_cast<QGraphicsSceneMouseEvent*>(event);

            if (mouse_event->button() == 1) {
                QPointF point = mouse_event->scenePos() / w_scale;

                point.rx() = floor(point.rx());
                point.ry() = floor(point.ry());

                QGraphicsItem* pressed = itemAt(point * w_scale, QTransform());

                if (pressed != nullptr && pressed->type() != 3){
                    qDebug() << "ObjID: " <<
                                static_cast<WorldItem*>(pressed)
                                ->getBoundObject()->ID  << " pressed.";

                    // Emit selected item to MapWindow
                    std::shared_ptr<Course::GameObject> obj
                            = static_cast<WorldItem*>(pressed)->getBoundObject();
                    emit objectClicked(obj);
                    highlightSelection(obj->getCoordinate());
                    return true;
                }

            }
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

// Not implemented yet
void WorldScene::highlightSelection(Course::Coordinate coord)
{
    qDebug() << "WorldScene::highlightSelection()";

    /*
    QPoint location = coord.asQpoint();
    QRectF highlightRect = QRectF(location * w_scale,
                                 location * w_scale + QPoint(w_scale, w_scale));

    QGraphicsRectItem* rect = new QGraphicsRectItem();
    rect->setRect(highlightRect);
    rect->setPen(QColor(250, 120, 255));
    rect->setBrush(QColor(250, 120, 255));
    addItem(rect);
    rect->setZValue(5);
    rect->setVisible(true);
    rect->update();

    QPainter* painter = new QPainter();
    painter->setPen(QColor(250, 120, 255));
    painter->setBrush(QColor(250, 120, 255));
    painter->drawRect(highlightRect);*/
    //this->update();
    //views().at(0)->update();
}
