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
};

#endif // CAMPUS_HH
