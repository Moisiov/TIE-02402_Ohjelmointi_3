#ifndef WORLDSCENE_H
#define WORLDSCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

#include <map>
#include <memory>

#include "core/gameobject.h"

const std::pair<int, int> SCENE_WIDTH_LIMITS = {1, 100};
const std::pair<int, int> SCENE_HEIGHT_LIMITS = {1, 100};
const std::pair<int, int> SCENE_SCALE_LIMITS = {1, 500};

/**
 * @brief The WorldScene is a custom QGraphicsScene which renders the game world.
 */
class WorldScene : public QGraphicsScene
{
    Q_OBJECT

public:
    WorldScene(QWidget* qt_parent = nullptr,
               int width = 10,
               int height = 10,
               int scale = 50
       );

    ~WorldScene() = default;

    void setSize(int width, int height);

    void setScale(int scale);

    void resize();

    int getScale() const;

    std::pair<int,int> getSize() const;

    void drawItem( std::shared_ptr<Course::GameObject> obj);

    void removeItem( std::shared_ptr<Course::GameObject> obj);

    void updateItem( std::shared_ptr<Course::GameObject> obj);

    virtual bool event(QEvent* event) override;

signals:
    void objectClicked(std::shared_ptr<Course::GameObject> obj);

private:
    QGraphicsItem* w_mapBoundRect;
    int w_width;
    int w_height;
    int w_scale;
};

#endif // WORLDSCENE_H
