#include "campus.hh"
#include "handlers/objectmanager.hh"

Campus::Campus(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
               const std::shared_ptr<Course::iObjectManager> &objectmanager,
               const std::shared_ptr<Course::PlayerBase> &owner,
               const int &tilespaces,
               const std::vector<Course::ResourceMap> &buildcost,
               const std::vector<Course::ResourceMap> &production,
               const unsigned int maxTier
               ):
    UpgradeableBuilding(eventhandler, objectmanager, owner, tilespaces, buildcost, production, maxTier),
    _objM(objectmanager),
    _progress(0)
{

}

std::string Campus::getType() const
{
    return "Campus";
}

void Campus::increaseProgress()
{
    std::shared_ptr<ObjectManager> objM = std::dynamic_pointer_cast<ObjectManager>(_objM);

    std::vector<std::shared_ptr<Course::WorkerBase>> workers = objM->getUnitsOnCoord(getCoordinate());

    unsigned increase = 0;

    for (unsigned i = 0; i < workers.size(); ++i) {
        std::string workerType = workers[i]->getType();
        if (workerType == "Teekkari") {
            increase += 5;
        } else if (workerType == "Scout") {
            // Scouts dont do research
        } else {
            increase += 1;
        }
    }

    _progress += increase;
}

unsigned Campus::getProgress()
{
    return _progress;
}

bool Campus::checkWinCondition()
{
    if (_progress >= 100) {
        return true;
    } else {
        return false;
    }
}
