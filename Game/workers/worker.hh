#ifndef WORKER_HH
#define WORKER_HH

#include "unitbase.hh"
#include "basicinfo.hh"

class Worker: public UnitBase
{
public:
    Worker(const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
           const std::shared_ptr<Course::iObjectManager>& objectmanager,
           const std::shared_ptr<Course::PlayerBase>& owner,
           const int& tilespaces = 1,
           const Course::ResourceMap& cost = BASIC_WORKER_BUILD_COST,
           const Course::ResourceMapDouble& efficiency = BASIC_WORKER_EFFICIENCY,
           unsigned movementMax = 2);

    virtual std::string getType() const override;
};

#endif // WORKER_HH
