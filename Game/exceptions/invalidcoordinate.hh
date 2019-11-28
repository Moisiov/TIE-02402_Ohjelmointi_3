#ifndef INVALIDCOORDINATE_HH
#define INVALIDCOORDINATE_HH

#include "exceptions/baseexception.h"

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
