#include "unitbase.hh"


UnitBase::UnitBase(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
                   const std::shared_ptr<Course::iObjectManager> &objectmanager,
                   const std::shared_ptr<Course::PlayerBase> &owner,
                   const int &tilespaces, const Course::ResourceMap &cost,
                   const Course::ResourceMapDouble &efficiency,
                   unsigned movementMax):
    Course::WorkerBase(eventhandler, objectmanager, owner, tilespaces, cost, efficiency),
    _movementMax(movementMax)
{

}

void UnitBase::rechargeMoves()
{
    _canMove = true;
}

void UnitBase::doSpecialAction()
{
    return; // We have no use for this
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
