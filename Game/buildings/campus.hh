#ifndef CAMPUS_HH
#define CAMPUS_HH

#include "upgradeablebuilding.hh"
#include "basicinfo.hh"

class Campus : public UpgradeableBuilding
{
public:
    Campus() = delete;

    explicit Campus(
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            const int& tilespaces = 1,
            const std::vector<Course::ResourceMap>& buildcost = CAMPUS_BUILD_COST_LIST,
            const std::vector<Course::ResourceMap>& production = CAMPUS_PRODUCTION_LIST,
            const unsigned int maxTier = 1
            );

    virtual ~Campus() = default;

    virtual std::string getType() const override;

    /**
     * @brief increaseProgress is called during turn changes to increment research
     * based on worker / teekkari count on the campus
     */
    void increaseProgress();

    /**
     * @brief getProgress returns unsigned value between 0-100 as to how much
     * research has been done
     */
    unsigned getProgress();

    /**
     * @brief checkWinCondition player has won the game if their campus research
     * reaches 100 points
     * @return true if 100 or over
     */
    bool checkWinCondition();

private:
    std::shared_ptr<Course::iObjectManager> _objM;
    unsigned _progress;
};

#endif // CAMPUS_HH
