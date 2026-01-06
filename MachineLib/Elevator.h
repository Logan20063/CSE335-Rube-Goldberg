/**
 * @file Elevator.h
 * @author Logan Bagdade
 *
 *
 */

#ifndef CANADIANEXPERIENCE_ELEVATOR_H
#define CANADIANEXPERIENCE_ELEVATOR_H
#include "Component.h"
#include "ISink.h"
#include "ISinkVisitor.h"

/**
 * The elevator component of the machine
 */
class Elevator : public Component, public ISink
{
private:

public:
    Elevator();

    void SetPosition(double x, double y);

    void Rectangle(double x, double y, double width = 0, double height = 0);

    void SetImage(std::wstring imageName);

    void SetWorld(std::shared_ptr<b2World> world) override;

    void Rotate(double rotation) override;

    /**
     * Accepts a visitor
     * @param visitor The visitor to accept
     */
    void Accept(ISinkVisitor* visitor) override { visitor->VisitElevator(this); }
};


#endif //CANADIANEXPERIENCE_ELEVATOR_H