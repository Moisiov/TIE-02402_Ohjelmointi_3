#ifndef HIGHLIGHTITEM_H
#define HIGHLIGHTITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <map>
#include <memory>

#include "core/coordinate.h"

/**
 * @brief The HighlightItem class is used to highlight selections on the WorldScene
 */
class HighlightItem : public QGraphicsItem
{
public:
    HighlightItem(Course::Coordinate coordinate, int size, QColor color = QColor(250, 120, 255, 50));

    QRectF boundingRect() const override;

    void paint (QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    void setColor(QColor color);

    void updateLocation(Course::Coordinate coordinate);

private:
    QPoint h_sceneLocation;
    int h_size;
    QColor h_color;
};

#endif // HIGHLIGHTITEM_H
