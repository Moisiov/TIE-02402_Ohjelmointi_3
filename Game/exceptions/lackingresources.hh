#ifndef LACKINGRESOURCES_HH
#define LACKINGRESOURCES_HH

#include "exceptions/illegalaction.h"

/**
 * @brief The LackingResources class is thrown whenever an action tries to spend
 * more resources than what the player can afford
 */
class LackingResources: public Course::IllegalAction
{
public:
    /**
     * @copydoc BaseException::BaseException
     */
    explicit LackingResources(const std::string& msg = ""):
        Course::IllegalAction(msg) {}

    /**
     * @copydoc BaseException::~BaseException
     */
    virtual ~LackingResources() = default;
};

#endif // LACKINGRESOURCES_HH
