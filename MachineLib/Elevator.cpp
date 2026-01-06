/**
 * @file Elevator.cpp
 * @author Logan Bagdade
 */

#include "pch.h"
#include "Elevator.h"

/**
 * Elevator constructor
 */
Elevator::Elevator() : Component()
{
    std::shared_ptr<cse335::PhysicsPolygon> shape = std::make_shared<cse335::PhysicsPolygon>();
    AddShape(shape);
}

/**
 * Sets the position of the elevator
 * @param x The x position of the elevator
 * @param y The y position of the elevator
 */
void Elevator::SetPosition(double x, double y)
{
    if (y > 402.5)
    {
        y -= 600;
    }
    Component::SetPosition(wxPoint(x, y));
    GetShapes().at(0)->SetPosition(x, y);
}

/**
 * Sets the image of the elevator
 * @param imageName The image file of the elevator
 */
void Elevator::SetImage(std::wstring imageName)
{
    GetShapes().at(0)->SetImage(imageName);
}

/**
 * Sets the elevator as a rectangle
 * @param x The x coordinate of the elevator
 * @param y The y coordinate of the elevator
 * @param width The width of the elevator
 * @param height The height of the elevator
 */
void Elevator::Rectangle(double x, double y, double width, double height)
{
    GetShapes().at(0)->Rectangle(x, y, width, height);
}

/**
 * Sets the world the elevator is in
 * @param world The world to associate with the elevator
 */
void Elevator::SetWorld(std::shared_ptr<b2World> world)
{
    GetShapes().at(0)->InstallPhysics(world);
}

/**
 * Rotates the elevator
 * @param rotation How much to move the elevator
 */
void Elevator::Rotate(double rotation)
{
    auto shape = GetShapes().at(0);
    auto position = shape->GetPosition();
    SetPosition(position.m_x, position.m_y + rotation * 190);
}