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
    HighlightItem(Course::Coordinate coordinate, int size,
                  QColor color = QColor(150, 255, 150, 150),
                  QColor borderColor = QColor(Qt::green));

    QRectF boundingRect() const override;

    void paint (QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    void setColor(QColor color);

    void updateLocation(Course::Coordinate coordinate);

    QPoint getLocation();

private:
    QPoint h_sceneLocation;
    int h_size;
    QColor h_color;
    QColor h_borderColor;
};

#endif // HIGHLIGHTITEM_H
