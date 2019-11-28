#ifndef LACKINGRESOURCES_HH
#define LACKINGRESOURCES_HH

#include "exceptions/illegalaction.h"

class LackingResources: public Course::IllegalAction
{
public:
    /**
     * @copydoc BaseException::BaseException
     */
    explicit LackingResources(const std::string& msg = ""):
        IllegalAction(msg) {}

    /**
     * @copydoc BaseException::~BaseException
     */
    virtual ~LackingResources() = default;
};

#endif // LACKINGRESOURCES_HH
