/**
 * @file SpeedVisitor.h
 * @author Logan Bagdade
 *
 *
 */

#ifndef CANADIANEXPERIENCE_SPEEDVISITOR_H
#define CANADIANEXPERIENCE_SPEEDVISITOR_H
#include "ISinkVisitor.h"

/**
 * A class that sets the speed of pullies
 */
class SpeedVisitor : public ISinkVisitor
{
private:
    ///The speed to set pulleys
    double mSpeed;

public:
    ///Deletes the default constructor
    SpeedVisitor() = delete;

    SpeedVisitor(double speed);
    void VisitPulley(Pulley* pulley) override;
};


#endif //CANADIANEXPERIENCE_SPEEDVISITOR_H