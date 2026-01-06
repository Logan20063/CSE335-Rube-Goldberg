/**
 * @file Shape.h
 * @author Logan Bagdade
 *
 *
 */

#ifndef CANADIANEXPERIENCE_SHAPE_H
#define CANADIANEXPERIENCE_SHAPE_H

#include "Component.h"
#include "ISink.h"
#include "ISinkVisitor.h"

/**
 * A shape component of the machine
 */
class Shape : public Component, public ISink
{
private:

public:
    Shape();

    void Rectangle(double x, double y, double width = 0, double height = 0);

    void SetImage(std::wstring imageLink);

    void SetInitialPosition(double x, double y);
    void SetInitialPosition(wxPoint pos);
    void SetInitialRotation(double rotation);

    void AddPoint(double x, double y);
    void Circle(double radius);
    void SetDynamic();
    void SetPhysics(double density, double friction, double restitution);
    void SetWorld(std::shared_ptr<b2World> world) override;

    void Rotate(double rotation) override;
    void BottomCenteredRectangle(double width, double height);

    void SetKinematic();

    /**
     * Accepts a visitor
     * @param visitor The visitor to accept
     */
    void Accept(ISinkVisitor* visitor) override { visitor->VisitShape(this); }
};


#endif //CANADIANEXPERIENCE_SHAPE_H