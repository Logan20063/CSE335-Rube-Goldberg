/**
 * @file Component.h
 * @author Logan Bagdade
 *
 *
 */

#ifndef CANADIANEXPERIENCE_COMPONENT_H
#define CANADIANEXPERIENCE_COMPONENT_H

#include <vector>

#include "PhysicsPolygon.h"

class Machine;

/**
 * A class for the components of the machine
 */
class Component
{
private:
    ///The position of the Component
    wxPoint mPosition = wxPoint(0, 0);

    ///The rotation angle of this Component
    double mAngle = 0;

    ///The list of polygons of the component
    std::vector<std::shared_ptr<cse335::PhysicsPolygon>> mShapes;

    ///The machine this component is a part of
    Machine* mMachine = nullptr;

public:
    virtual ~Component() = default;
    /**
     * Sets the new location of the component
     * @param location The new location of the Component
     */
    void SetPosition(wxPoint location) { mPosition = location; }

    /**
     * Gets the position of the component
     * @return The position of the component
     */
    wxPoint GetPosition() { return mPosition; }

    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    /**
     * Returns mShapes
     * @return The reference to the vector of shapes
     */
    std::vector<std::shared_ptr<cse335::PhysicsPolygon>>& GetShapes() { return mShapes; }

    /**
     * Adds a shape to the component vector
     * @param shape The shape to add to the component
     */
    void AddShape(std::shared_ptr<cse335::PhysicsPolygon> shape) { mShapes.push_back(shape); }

    /**
     * Sets the world of the component(disabled)
     * @param world The world to set the component to
     */
    virtual void SetWorld(std::shared_ptr<b2World> world) = 0;

    /**
     * Superclass virtual function that updates component
     * @param elapsed How long it has been since the last update
     */
    virtual void Update(double elapsed) {}

    /**
     * Associates a machine with this component
     * @param pMachine The machine to associate with this component
     */
    void SetMachine(Machine* pMachine) { mMachine = pMachine; }

    /**
     * Gets the machine associated with the component
     * @return The machine associated with this component
     */
    Machine* GetMachine() { return mMachine; }
};


#endif //CANADIANEXPERIENCE_COMPONENT_H