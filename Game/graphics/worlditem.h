#ifndef WORLDITEM_H
#define WORLDITEM_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>

#include <memory>
#include <map>

#include "core/gameobject.h"
#include "handlers/objectmanager.hh"

/**
 * @brief The WorldItem is a QGraphicsItem class which
 * defines how single object is drawn on the WorldScene.
 */
class WorldItem : public QGraphicsItem
{
public:
    WorldItem(const std::shared_ptr<Course::GameObject> &obj, int size);

    QRectF boundingRect() const override;

    void paint (QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    const std::shared_ptr<Course::GameObject> &getBoundObject();

    void updateLoc();

    bool isSameObj(std::shared_ptr<Course::GameObject> obj);

    int getSize() const;

    void setSize(int size);

    /**
     * @brief drawPlayerMarker draws a sign showing the owner of building/worker
     * @param painter
     */
    void drawPlayerMarker(QPainter *painter);

    /**
     * @brief getImgOffset checks if image needs to be moved
     * - now checking if tile contains multiple workers returns correct offset
     * to draw workers next to each other
     * @return offset as QPoint value
     */
    QPoint getImgOffset();

    /**
     * @brief setZVal set Z value according to the object type
     */
    void setZVal();

private:
    const std::shared_ptr<Course::GameObject> w_gameobject;
    QPoint w_scenelocation;
    int w_size;

    static std::map<std::string, QColor> c_mapcolors;
    static void addNewColor(std::string type);

    static std::map<std::string, QString> _pixmapUrls;
};

#endif // WORLDITEM_H
