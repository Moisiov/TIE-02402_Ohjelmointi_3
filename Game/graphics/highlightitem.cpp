#include "highlightitem.h"
#include <QDebug>

HighlightItem::HighlightItem(Course::Coordinate coordinate, int size, QColor color,
                             QColor borderColor):
    h_sceneLocation(coordinate.asQpoint()),
    h_size(size),
    h_color(color),
    h_borderColor(borderColor)
{
    setZValue(2);
}

QRectF HighlightItem::boundingRect() const
{
    return QRectF(h_sceneLocation * h_size, h_sceneLocation * h_size + QPoint(h_size, h_size));
}

void HighlightItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED( option ); Q_UNUSED( widget );
    QPoint radialCenter = h_sceneLocation*h_size + QPoint(h_size/2, h_size/2);
    QRadialGradient gradient(radialCenter, h_size);
    QColor opaqueColor = h_color;
    opaqueColor.setAlpha(0);
    gradient.setColorAt(0, opaqueColor);
    gradient.setColorAt(1, h_color);

    QBrush brush(gradient);
    painter->setBrush(brush);
    painter->setPen(h_borderColor);
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
