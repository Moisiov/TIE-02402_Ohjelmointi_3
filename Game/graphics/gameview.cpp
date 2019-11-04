#include "gameview.h"
#include <QDebug>

GameView::GameView(QWidget* parent):
    QGraphicsView(parent)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    this->installEventFilter(this);

    // Turn off scroll bars
    this->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    this->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
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
            this->setDragMode(QGraphicsView::DragMode::ScrollHandDrag);
            // Emit left click
            QMouseEvent* pressEvent = new QMouseEvent(QEvent::GraphicsSceneMousePress,
                                            mouse_event->pos(), Qt::MouseButton::LeftButton,
                                            Qt::MouseButton::LeftButton, Qt::KeyboardModifier::NoModifier);

            this->mousePressEvent(pressEvent);
        }
    }

    Q_UNUSED(object)
    return false;
}

void GameView::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == 2) {
        this->setDragMode(QGraphicsView::DragMode::NoDrag);
    }
}
