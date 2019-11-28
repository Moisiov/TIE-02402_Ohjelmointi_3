#include "worldscene.h"
#include "worlditem.h"
#include "mapwindow.hh"
#include "highlightitem.h"

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
    w_highlightedTiles({})
{
    setSize(width, height);
    setScale(scale);

    // set black background
    setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
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
    if(views().at(0)->dragMode() != QGraphicsView::DragMode::ScrollHandDrag)
    {
        if(event->type() == QEvent::GraphicsSceneMousePress)
        {
            QGraphicsSceneMouseEvent* mouse_event =
                    dynamic_cast<QGraphicsSceneMouseEvent*>(event);

            if (mouse_event->button() == 1) {
                QPointF point = mouse_event->scenePos() / w_scale;

                point.rx() = floor(point.rx());
                point.ry() = floor(point.ry());

                if (point.rx() >= 0 && point.ry() >= 0
                        && point.rx() < w_width && point.ry() < w_height) {
                    QGraphicsItem* pressed = items(point * w_scale).last();

                    if (pressed != nullptr && pressed->type() != 3){
                        qDebug() << "ObjID: " <<
                                    static_cast<WorldItem*>(pressed)
                                    ->getBoundObject()->ID  << " pressed.";

                        // Emit selected item to MapWindow
                        std::shared_ptr<Course::GameObject> obj
                                = static_cast<WorldItem*>(pressed)->getBoundObject();
                        emit objectClicked(obj);
                        return true;
                    }
                }
            }
        }
    }

    // Hover events not working yet
    /*if (event->type() == QEvent::GraphicsSceneHoverEnter)
    {
        QGraphicsSceneMouseEvent* mouse_event =
                dynamic_cast<QGraphicsSceneMouseEvent*>(event);
        QPointF point = mouse_event->scenePos() / w_scale;

        point.rx() = floor(point.rx());
        point.ry() = floor(point.ry());

        highlightTile(Course::Coordinate(static_cast<int>(point.rx()), static_cast<int>(point.ry())));
    }

    if (event->type() == QEvent::GraphicsSceneHoverLeave)
    {
        // clearHighlight();
    }*/

    return QGraphicsScene::event(event);
}

void WorldScene::removeItem(std::shared_ptr<Course::GameObject> obj)
{
    QList<QGraphicsItem*> items_list = items(obj->getCoordinate().asQpoint() * w_scale);
    if ( items_list.size() == 1 ){
        throw GraphicsException("Nothing to be removed at the location pointed by given obj.");
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

void WorldScene::highlightTile(Course::Coordinate coord, bool clear)
{
    if (clear) {clearHighlight();}

    if (coord.x() >= 0 && coord.y() >= 0 && coord.x() < w_width && coord.y() < w_height)
    {
        HighlightItem* item = new HighlightItem(coord, w_scale);
        addItem(item);

        w_highlightedTiles.push_back(item);
    }
}

void WorldScene::highlightSelection(std::vector<Course::Coordinate> coords)
{
    clearHighlight();

    for (auto coord : coords)
    {
        highlightTile(coord, false);
    }
}

void WorldScene::clearHighlight()
{
    for (auto hItem : w_highlightedTiles)
    {
        delete hItem;
    }
    w_highlightedTiles.clear();
    update();
}
