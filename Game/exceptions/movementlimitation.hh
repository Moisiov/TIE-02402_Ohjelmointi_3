#ifndef MOVEMENTLIMITATION_HH
#define MOVEMENTLIMITATION_HH

#include "exceptions/illegalaction.h"

class MovementLimitation: public Course::IllegalAction
{
public:
    /**
     * @copydoc BaseException::BaseException
     */
    explicit MovementLimitation(const std::string& msg = ""):
        Course::IllegalAction(msg) {}

    /**
     * @copydoc BaseException::~BaseException
     */
    virtual ~MovementLimitation() = default;
};

#endif // MOVEMENTLIMITATION_HH
