/**
 * @file ISinkVisitor.h
 * @author Logan Bagdade
 *
 */

#ifndef CANADIANEXPERIENCE_ISINKVISITOR_H
#define CANADIANEXPERIENCE_ISINKVISITOR_H

class Conveyor;
class Pulley;
class Elevator;
class Shape;

/**
 * Interface for sink visitors
 */
class ISinkVisitor
{
private:

public:
    virtual ~ISinkVisitor() = default;

    /**
     * Visits a conveyor
     * @param conveyor The conveyor to visit
     */
    virtual void VisitConveyor(Conveyor* conveyor) {}

    /**
     * Visits a pulley
     * @param pulley The pulley to visit
     */
    virtual void VisitPulley(Pulley* pulley) {}

    /**
     * Visits a elevator
     * @param elevator The elevator to visit
     */
    virtual void VisitElevator(Elevator* elevator) {}

    /**
     * Visits a shape
     * @param shape The shape to visit
     */
    virtual void VisitShape(Shape* shape) {}
};


#endif //CANADIANEXPERIENCE_ISINKVISITOR_H