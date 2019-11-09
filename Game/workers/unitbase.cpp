#include "unitbase.hh"

UnitBase::UnitBase(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
                   const std::shared_ptr<Course::iObjectManager> &objectmanager,
                   const std::shared_ptr<Course::PlayerBase> &owner,
                   unsigned movementMax):
    Course::WorkerBase(eventhandler, objectmanager, owner),
    _movementMax(movementMax),
    _canMove(false)
{

}

void UnitBase::rechargeMoves()
{
    _canMove = true;
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
