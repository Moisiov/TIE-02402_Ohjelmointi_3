#ifndef UNITBASE_HH
#define UNITBASE_HH

#include "workers/workerbase.h"
#include "basicinfo.hh"

class UnitBase: public Course::WorkerBase
{
public:
    UnitBase(const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
             const std::shared_ptr<Course::iObjectManager>& objectmanager,
             const std::shared_ptr<Course::PlayerBase>& owner,
             const int& tilespaces = 1,
             const Course::ResourceMap& cost = {},
             const Course::ResourceMapDouble& efficiency = {},
             unsigned movementMax = 3);

    bool canMove() const;
    unsigned moveRange() const;
    void wasMoved();
    void rechargeMoves();

    virtual void doSpecialAction() override;

private:
    unsigned _movementMax;
    bool _canMove;
};

#endif // UNITBASE_HH
