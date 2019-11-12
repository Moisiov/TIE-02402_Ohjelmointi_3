#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include <QtWidgets>
#include <QWidget>

/**
 * @brief The GameView class is a custom QGraphicsView class
 */
class GameView : public QGraphicsView
{
public:
    GameView(QWidget* parent = 0);

    /**
     * @brief wheelEvent allows view scaling by scrolling the mouse wheel
     * @param event is catched QWheelEvent
     */
    void wheelEvent(QWheelEvent* event);

    /**
     * @brief eventFilter is a custom event filter for view click events.
     * Mouse right click changes DragMode to ScrollHandDrag and emits left click
     * to allow dragging.
     * @param obj target object (not used in this implementation)
     * @param event catched view event
     * @return false to contunue the event chain
     */
    bool eventFilter(QObject *obj, QEvent *event);

    /**
     * @brief mouseReleaseEvent catches the mouse release event when dragging the map
     * @param event catched mouse release
     */
    void mouseReleaseEvent(QMouseEvent *event);

private:
    int _originX;
    int _originY;
};

#endif // GAMEVIEW_H
