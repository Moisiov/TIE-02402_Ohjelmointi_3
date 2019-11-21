#include "highlightitem.h"

HighlightItem::HighlightItem(Course::Coordinate coordinate, int size, QColor color,
                             QColor borderColor):
    h_sceneLocation(coordinate.asQpoint()),
    h_size(size),
    h_color(color),
    h_borderColor(borderColor)
{
}

QRectF HighlightItem::boundingRect() const
{
    return QRectF(h_sceneLocation * h_size, h_sceneLocation * h_size + QPoint(h_size, h_size));
}

void HighlightItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED( option ); Q_UNUSED( widget );
    painter->setPen(h_borderColor);
    painter->setBrush(h_color);
    painter->drawRect(boundingRect());
}

void HighlightItem::setColor(QColor color)
{
    h_color = color;
}

void HighlightItem::updateLocation(Course::Coordinate coordinate)
{
    h_sceneLocation = coordinate.asQpoint();
}

QPoint HighlightItem::getLocation()
{
    return h_sceneLocation;
}
