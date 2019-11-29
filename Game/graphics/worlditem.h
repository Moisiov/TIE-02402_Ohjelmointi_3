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

    void drawPlayerMarker(QPainter *painter);

    QPoint getImgOffset();

private:
    const std::shared_ptr<Course::GameObject> w_gameobject;
    QPoint w_scenelocation;
    int w_size;

    static std::map<std::string, QColor> c_mapcolors;
    static void addNewColor(std::string type);

    static std::map<std::string, QString> _pixmapUrls;
};

#endif // WORLDITEM_H
