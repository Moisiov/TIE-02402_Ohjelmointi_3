#ifndef UNITBASE_HH
#define UNITBASE_HH

#include "workers/workerbase.h"
#include "basicinfo.hh"

/**
 * @brief The UnitBase class extends WorkerBase by adding unit movement options
 * and also redefines worker efficiency as there was a need to be able to edit it
 * during unit specialization
 */
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

    void setEfficiency(Course::ResourceMapDouble efficiency);
    Course::ResourceMapDouble getEfficiency();

    virtual void doSpecialAction() override;

    std::string description();

    bool canUpgrade();

private:
    Course::ResourceMapDouble _efficiency;
    unsigned _movementMax;
    bool _canMove;
};

#endif // UNITBASE_HH
