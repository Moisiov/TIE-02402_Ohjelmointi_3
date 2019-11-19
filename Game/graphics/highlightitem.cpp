#include "highlightitem.h"

HighlightItem::HighlightItem(Course::Coordinate coordinate, int size, QColor color):
    h_sceneLocation(coordinate.asQpoint()),
    h_size(size),
    h_color(color)
{
}

QRectF HighlightItem::boundingRect() const
{
    return QRectF(h_sceneLocation * h_size, h_sceneLocation * h_size + QPoint(h_size, h_size));
}

void HighlightItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED( option ); Q_UNUSED( widget );
    painter->setBrush(h_color);
    painter->drawRect(boundingRect());
    update();
}

void HighlightItem::setColor(QColor color)
{
    h_color = color;
}

void HighlightItem::updateLocation(Course::Coordinate coordinate)
{
    h_sceneLocation = coordinate.asQpoint();
}
