#ifndef INVALIDCOORDINATE_HH
#define INVALIDCOORDINATE_HH

#include "exceptions/baseexception.h"

/**
 * @brief The InvalidCoordinate class is thrown when a given coordinate is outside
 * of map limitations and cannot be accessed
 */
class InvalidCoordinate: public Course::BaseException
{
public:
    /**
     * @copydoc BaseException::BaseException
     */
    explicit InvalidCoordinate(const std::string& msg = ""):
        Course::BaseException(msg) {}

    /**
     * @copydoc BaseException::~BaseException
     */
    virtual ~InvalidCoordinate() = default;
};


#endif // INVALIDCOORDINATE_HH
