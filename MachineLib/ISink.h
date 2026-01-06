/**
 * @file ISink.h
 * @author Logan Bagdade
 *
 *
 */

#ifndef CANADIANEXPERIENCE_ISINK_H
#define CANADIANEXPERIENCE_ISINK_H
#include "ISinkVisitor.h"

/**
 * An interface class for all rotation sinks
 */
class ISink
{
private:

public:
    /**
     * Class that runs when the sink needs to rotate(disabled)
     * @param rotation How much to rotate the sink by
     */
    virtual void Rotate(double rotation) = 0;

    /**
     * Accepts a visitor(disabled)
     * @param visitor the visitor to accept
     */
    virtual void Accept(ISinkVisitor* visitor) = 0;
};


#endif //CANADIANEXPERIENCE_ISINK_H