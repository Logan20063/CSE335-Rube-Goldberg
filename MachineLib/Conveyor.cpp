/**
 * @file Conveyor.cpp
 * @author Logan Bagdade
 */

#include "pch.h"
#include "Conveyor.h"

#include "b2_contact.h"

/// The offset from the bottom center of the conveyor
/// to the center of the drive shaft.  48
const auto ConveyorShaftOffset = wxPoint2DDouble(48, 4);

/// The size of the conveyor in cm
const auto ConveyorSize = wxSize(125, 14);

/// The conveyor image to use
const std::wstring ConveyorImageName = L"/conveyor.png";

/**
 * Conveyor constructor
 * @param imageDir The path to the image directory
 */
Conveyor::Conveyor(std::wstring imageDir)
{
    std::shared_ptr<cse335::PhysicsPolygon> conveyor = std::make_shared<cse335::PhysicsPolygon>();
    conveyor->BottomCenteredRectangle(ConveyorSize);
    conveyor->SetImage(imageDir + ConveyorImageName);
    AddShape(conveyor);
}

/**
 * Sets the position of the conveyor
 * @param x The x position of the conveyor
 * @param y The y position of the conveyor
 */
void Conveyor::SetPosition(double x, double y)
{
    Component::SetPosition(wxPoint(x, y));
    GetShapes().at(0)->SetPosition(x, y);
}

/**
 * Installs the physics onto the conveyor
 * @param world The world to add the conveyor to
 */
void Conveyor::SetWorld(std::shared_ptr<b2World> world)
{
    GetShapes().at(0)->InstallPhysics(world);
}

/**
 * Returns the position of the shaft of the conveyor
 * @return The position a pulley connected to the conveyor should go
 */
wxPoint Conveyor::GetShaftPosition()
{
    return wxPoint(GetPosition().x + ConveyorShaftOffset.m_x, GetPosition().y + ConveyorShaftOffset.m_y);
}

/**
 * Sets the tangential speed of objects contacted to the conveyor
 * @param rotation how much to move the conveyor
 */
void Conveyor::Rotate(double rotation)
{
    auto contact = GetShapes().at(0)->GetBody()->GetContactList();
    while(contact != nullptr)
    {
        if(contact->contact->IsTouching())
        {
            contact->other->SetLinearVelocity(b2Vec2(rotation * 30, 0));
        }

        contact = contact->next;
    }
}
