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
    /**
     * @brief HighlightItem constructor
     * @param coordinate highlight location
     * @param size highlight size (should be the same as GraphicsScene scale)
     * @param color highlight color (default pink)
     * @param borderColor highlight border color (default pink)
     */
    HighlightItem(Course::Coordinate coordinate, int size,
                  QColor color = QColor(230, 130, 230, 150),
                  QColor borderColor = QColor(230, 130, 230));

    QRectF boundingRect() const override;

    void paint (QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    void setColor(QColor color);

    QPoint getLocation();

private:
    QPoint h_sceneLocation;
    int h_size;
    QColor h_color;
    QColor h_borderColor;
};

#endif // HIGHLIGHTITEM_H
