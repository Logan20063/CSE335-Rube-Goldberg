/**
 * @file Conveyor.h
 * @author Logan Bagdade
 *
 *
 */

#ifndef CANADIANEXPERIENCE_CONVEYOR_H
#define CANADIANEXPERIENCE_CONVEYOR_H

#include "Component.h"
#include "ISink.h"
#include "ISinkVisitor.h"

/**
 * The conveyor component of the machine
 */
class Conveyor : public Component, public ISink
{
private:

public:
    Conveyor(std::wstring imageDir);

    void SetPosition(double x, double y);

    void SetWorld(std::shared_ptr<b2World> world) override;
    wxPoint GetShaftPosition();

    void Rotate(double rotation) override;

    /**
     * Accepts a visitor
     * @param visitor The visitor to accept
     */
    void Accept(ISinkVisitor* visitor) override { visitor->VisitConveyor(this); }
};


#endif //CANADIANEXPERIENCE_CONVEYOR_H