/**
 * @file Shape.cpp
 * @author Logan Bagdade
 */

#include "pch.h"
#include "Shape.h"

/**
 * The constructor for shape
 */
Shape::Shape() : Component()
{
    AddShape(std::make_shared<cse335::PhysicsPolygon>());
}

/**
 * Makes the shape a rectangle
 * @param x the x pos of the bottom-left corner
 * @param y the y pos of the bottom-left corner
 * @param width the width of the rectangle
 * @param height the height of the rectanglr
 */
void Shape::Rectangle(double x, double y, double width, double height)
{
    GetShapes().at(0)->Rectangle(x, y, width, height);
}

/**
 * Sets the image of the shape
 * @param imageLink The link to the image
 */
void Shape::SetImage(std::wstring imageLink)
{
    GetShapes().at(0)->SetImage(imageLink);
}

/**
 * Sets the initial position of the shape
 * @param x The x position of the shape
 * @param y the y position of the shape
 */
void Shape::SetInitialPosition(double x, double y)
{
    SetPosition(wxPoint(x, y));
    GetShapes().at(0)->SetInitialPosition(x, y);
}

/**
 * Sets the initial position of the shape
 * @param pos The position of the shape
 */
void Shape::SetInitialPosition(wxPoint pos)
{
    SetPosition(pos);
    GetShapes().at(0)->SetInitialPosition(pos.x, pos.y);
}

/**
 * Sets the initial rotation of the shape
 * @param rotation The initial rotation angle of the shape
 */
void Shape::SetInitialRotation(double rotation)
{
    GetShapes().at(0)->SetInitialRotation(rotation);
}


/**
 * Adds a new point to the shape
 * @param x the x position of the new point
 * @param y the y position of the new point
 */
void Shape::AddPoint(double x, double y)
{
    GetShapes().at(0)->AddPoint(x, y);
}

/**
 * Makes the shape a circle
 * @param radius The radius of the shape
 */
void Shape::Circle(double radius)
{
    GetShapes().at(0)->Circle(radius);
}

/**
 * Sets the shape as dynamic
 */
void Shape::SetDynamic()
{
    GetShapes().at(0)->SetDynamic();
}

/**
 * Sets physics constants for this shape
 * @param density The density of this shape
 * @param friction The friction coefficient of the shape
 * @param restitution The elasticity of this shape
 */
void Shape::SetPhysics(double density, double friction, double restitution)
{
    GetShapes().at(0)->SetPhysics(density, friction, restitution);
}

/**
 * Sets a world to the shape
 * @param world The world to put the shape in
 */
void Shape::SetWorld(std::shared_ptr<b2World> world)
{
    GetShapes().at(0)->InstallPhysics(world);
}

/**
 * Rotates the shape
 * @param rotation How much to rotate
 */
void Shape::Rotate(double rotation)
{
    //GetShapes().at(0)->SetRotation(GetShapes().at(0)->GetRotation() + rotation);
    GetShapes().at(0)->SetAngularVelocity(rotation * 15);
}

/**
 * Makes the shape a bottom centered rectangle
 * @param width The width of the shape
 * @param height The height of the shape
 */
void Shape::BottomCenteredRectangle(double width, double height)
{
    GetShapes().at(0)->BottomCenteredRectangle(width, height);
}

/**
 * Sets the shape to be able to move and rotate
 */
void Shape::SetKinematic()
{
    GetShapes().at(0)->SetKinematic();
}


