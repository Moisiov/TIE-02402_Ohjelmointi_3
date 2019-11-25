#include "worker.hh"

Worker::Worker(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
               const std::shared_ptr<Course::iObjectManager> &objectmanager,
               const std::shared_ptr<Course::PlayerBase> &owner,
               const int &tilespaces,
               const Course::ResourceMap &cost,
               const Course::ResourceMapDouble &efficiency,
               unsigned movementMax):
    UnitBase(eventhandler, objectmanager, owner, tilespaces, cost, efficiency, movementMax),
    _type("Worker")
{

}

std::string Worker::getType() const
{
    return _type;
}

bool Worker::specializeInto(std::string type)
{
    if (SPECIALIZATION_COST.find(type) == SPECIALIZATION_COST.end()) {
        qDebug() << "Worker class doesn't recognize specialization type!";
        return false;
    }

    _type = type;

    Course::ResourceMapDouble efficiency = SPECIALIZATION_EFFICIENCY.find(type)->second;
    setEfficiency(efficiency);

    return true;
}
