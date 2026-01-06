/**
 * @file Machine.cpp
 * @author Logan Bagdade
 */

#include "pch.h"
#include "Machine.h"
#include "Component.h"
#include "ContactListener.h"
#include <sstream>

/**
 * Machine constructor
 * @param number The number of the machine
 */
Machine::Machine(int number)
{
    mNumber = number;
    mWorld = std::make_shared<b2World>(b2Vec2(0.0f, -9.8f));

    // Create and install the contact filter
    mContactListener = std::make_shared<ContactListener>();
    mWorld->SetContactListener(mContactListener.get());
}

/**
 * Draws the machine
 * @param graphics The graphics to draw the machine
 */
void Machine::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();
    graphics->Translate(mLocation.x, mLocation.y);
    graphics->Scale(1.5, -1.5);

    // Draw your machine assuming an origin of 0,0

    for (std::shared_ptr<Component> component : mComponents)
    {
        component->Draw(graphics);
    }

    graphics->PopState();
}

/**
 * Resets the machine
 */
void Machine::Reset()
{

}

/**
 * Gets the location of the machine
 * @return The location of the machine
 */
wxPoint Machine::GetLocation()
{
    return mLocation;
}

/**
 * Sets the location of the machine
 * @param pLocation The location of the machine
 */
void Machine::SetLocation(wxPoint pLocation)
{
    mLocation = pLocation;
}

/**
 * Updates the machine
 * @param elapsed How much time has passed
 */
void Machine::Update(double elapsed)
{
    mWorld->Step(elapsed, 6, 6);
    for (std::shared_ptr<Component> component : mComponents)
    {
        component->Update(elapsed);
    }
}

/**
 * Adds a component to the machine
 * @param pComponent the component to add to the machine
 */
void Machine::AddComponent(std::shared_ptr<Component> pComponent)
{
    pComponent->SetWorld(mWorld);
    pComponent->SetMachine(this);
    mComponents.push_back(pComponent);
}

/**
 * Returns the physics world of the machine
 * @return the world of the machine
 */
std::shared_ptr<b2World> Machine::GetWorld()
{
    return mWorld;
}

// void Machine::SetMachineFrame(int frame)
// {
//     int pastFrame = mMachineSystem->GetFrame()
//     double frameRate = mMachineSystem->GetFrameRate();
// }

