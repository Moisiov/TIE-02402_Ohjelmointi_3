#ifndef WORLDITEM_H
#define WORLDITEM_H

#include <QGraphicsItem>
#include <QPainter>

#include <memory>
#include <map>

#include "core/gameobject.h"

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

private:
    const std::shared_ptr<Course::GameObject> w_gameobject;
    QPoint w_scenelocation;
    int w_size;

    static std::map<std::string, QColor> c_mapcolors;
    static void addNewColor(std::string type);
};

#endif // WORLDITEM_H
