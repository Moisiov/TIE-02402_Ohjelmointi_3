#include "unitbase.hh"
#include "player.hh"


UnitBase::UnitBase(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
                   const std::shared_ptr<Course::iObjectManager> &objectmanager,
                   const std::shared_ptr<Course::PlayerBase> &owner,
                   const int &tilespaces, const Course::ResourceMap &cost,
                   const Course::ResourceMapDouble &efficiency,
                   unsigned movementMax):
    Course::WorkerBase(eventhandler, objectmanager, owner, tilespaces, cost, efficiency),
    _efficiency(efficiency),
    _movementMax(movementMax),
    _canMove(true)
{

}

void UnitBase::rechargeMoves()
{
    _canMove = true;
}

void UnitBase::setEfficiency(Course::ResourceMapDouble efficiency)
{
    _efficiency = efficiency;
}

Course::ResourceMapDouble UnitBase::getEfficiency()
{
    return _efficiency;
}

void UnitBase::doSpecialAction()
{
    return; // We have no use for this
}

std::string UnitBase::description()
{
    std::string description = "";
    description += getOwner()->getName() + "'s ";
    description += getType();

    return description;
}

bool UnitBase::canUpgrade()
{
    if (getType() == "Worker") {
        return true;
    } else {
        return false;
    }
}


bool UnitBase::canMove() const
{
    return _canMove;
}

unsigned UnitBase::moveRange() const
{
    return _movementMax;
}

void UnitBase::wasMoved()
{
    _canMove = false;
}
