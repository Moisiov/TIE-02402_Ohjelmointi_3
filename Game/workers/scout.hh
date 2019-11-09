#ifndef SCOUT_HH
#define SCOUT_HH

#include "unitbase.hh"
#include "basicinfo.hh"

class Scout: public UnitBase
{
public:
    Scout(const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
          const std::shared_ptr<Course::iObjectManager>& objectmanager,
          const std::shared_ptr<Course::PlayerBase>& owner,
          const int& tilespaces = 1,
          const Course::ResourceMap& cost = SCOUT_BUILD_COST,
          const Course::ResourceMapDouble& efficiency = SCOUT_EFFICIENCY,
          unsigned movementMax = 4);

   virtual std::string getType() const override;
};

#endif // SCOUT_HH
