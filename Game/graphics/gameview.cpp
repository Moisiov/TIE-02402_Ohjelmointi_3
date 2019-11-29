#include "gameview.h"

#include <QDebug>

GameView::GameView(QWidget* parent):
    QGraphicsView(parent)
{
    // setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    installEventFilter(this);

    // Turn off scroll bars
    setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
}

void GameView::wheelEvent(QWheelEvent *event)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    double scaleMultiplier = 1.2;

    if(event->delta() > 0)
    {
        scale(scaleMultiplier, scaleMultiplier);
    }

    if(event->delta() < 0)
    {
        scale(1/scaleMultiplier, 1/scaleMultiplier);
    }
}

bool GameView::eventFilter(QObject *object, QEvent *event) {
    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);

        if (mouse_event->button() == 2)
        {
            // Enable dragging mode
            setDragMode(QGraphicsView::DragMode::ScrollHandDrag);
            // Emit left click to allow drag mode
            QMouseEvent* pressEvent = new QMouseEvent(QEvent::GraphicsSceneMousePress,
                                            mouse_event->pos(), Qt::MouseButton::LeftButton,
                                            Qt::MouseButton::LeftButton, Qt::KeyboardModifier::NoModifier);

            mousePressEvent(pressEvent);
            return true;
        }
    }

    // Q_UNUSED(object)
    return QGraphicsView::eventFilter(object, event);
}

void GameView::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == 2) {
        setDragMode(QGraphicsView::DragMode::NoDrag);
    }
}
