#ifndef WORLDSCENE_H
#define WORLDSCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

#include <map>
#include <memory>

#include "core/gameobject.h"
#include "tiles/tilebase.h"
#include "highlightitem.h"
#include "exceptions/graphicsexception.h"

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

    /**
     * @brief highlightTile highlights selected tile on scene
     * @param coord coordinate to be highlighted
     * @param clear is a boolean value that tells the function
     * if highlight area should be cleared before new highlight
     */
    void highlightTile(Course::Coordinate coord, bool clear = true);

    /**
     * @brief highlightSelection highlights selected tiles on scene
     * @param coords is a vector containing given coordinates
     */
    void highlightSelection (std::vector<Course::Coordinate> coords );

    /**
     * @brief clearHighLight removes highlighted area
     */
    void clearHighlight();

signals:
    /**
     * @brief objectClicked is sent when an object on the world scene is clicked
     * @param obj is the clicked object
     */
    void objectClicked(std::shared_ptr<Course::GameObject> obj);

private:
    int w_width;
    int w_height;
    int w_scale;

    // std::vector<std::shared_ptr<HighlightItem>> w_highlightedTiles;
    std::vector<HighlightItem*> w_highlightedTiles;
};

#endif // WORLDSCENE_H
