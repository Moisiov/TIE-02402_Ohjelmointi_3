#ifndef GRAPHICSEXCEPTION_H
#define GRAPHICSEXCEPTION_H

#include "exceptions/baseexception.h"

class GraphicsException: public Course::BaseException
{
public:
    /**
     * @copydoc BaseException::BaseException
     */
    explicit GraphicsException(const std::string& msg = ""):
        BaseException(msg) {}

    /**
     * @copydoc BaseException::~BaseException
     */
    virtual ~GraphicsException() = default;
};

#endif // GRAPHICSEXCEPTION_H
