/**
 * @file Pipe.cpp
 * @author Logan Bagdade
 */

#include "pch.h"
#include "Pipe.h"
#include "ContactListener.h"
#include "Machine.h"

/// The size of the pipe in centimeters
const double PipeSize = 50;

/// Delay between when the ball falls in the pipen, and when it is shot out
const double PipeDelay = 1.5;

/// The direction the ball is shot out of the pipe
const wxPoint2DDouble PipeShot = wxPoint2DDouble(1, 7);

/**
 * The pipe constructor
 * @param imageDir The path to the image directory
 */
Pipe::Pipe(std::wstring imageDir) : Component()
{
    std::shared_ptr<cse335::PhysicsPolygon> pipe = std::make_shared<cse335::PhysicsPolygon>();
    pipe->Rectangle(0, 0, PipeSize,PipeSize);
    pipe->SetImage(imageDir + L"/images/pipe.png");
    AddShape(pipe);

    std::shared_ptr<cse335::PhysicsPolygon> bottom = std::make_shared<cse335::PhysicsPolygon>();
    bottom->Rectangle(0, 10, PipeSize,5);
    bottom->SetColor(wxColour(255, 0, 0));
    bottom->SetKinematic();
    bottom->SetRotation(-.05);
    bottom->SetOpacity(0);
    AddShape(bottom);

    std::shared_ptr<cse335::PhysicsPolygon> left = std::make_shared<cse335::PhysicsPolygon>();
    left->Rectangle(0, 0, 5,PipeSize);
    left->SetColor(wxColour(255, 0, 0));
    left->SetOpacity(0);
    AddShape(left);

    std::shared_ptr<cse335::PhysicsPolygon> right = std::make_shared<cse335::PhysicsPolygon>();
    right->Rectangle(PipeSize-5, 0, 5,PipeSize);
    right->SetColor(wxColour(255, 0, 0));
    right->SetOpacity(0);
    AddShape(right);
}

/**
 * Adds the pipe to the world
 * @param world The world to add shapes to
 */
void Pipe::SetWorld(std::shared_ptr<b2World> world)
{
    auto shapes = GetShapes();
    shapes.at(1)->InstallPhysics(world);
    shapes.at(2)->InstallPhysics(world);
    shapes.at(3)->InstallPhysics(world);
}

/**
 * Updates the pipe
 * @param elapsed how long has elapsed since last update
 */
void Pipe::Update(double elapsed)
{
    if (mContact)
    {
        if (mRising)
        {
            if (mTime > PipeDelay)
            {
                double change = 50 * elapsed;
                auto shapes = GetShapes();
                auto position = shapes.at(1)->GetPosition();
                //shapes.at(1)->SetPosition(position.m_x, position.m_y + change);
                shapes.at(1)->SetAngularVelocity(change);
                mHeight += change;
                if (mHeight > 10)
                {
                    mRising = false;
                }
            }
            else
            {
                mTime += elapsed;
            }
        }
        else
        {
            double change = 50 * elapsed * -1;
            auto shapes = GetShapes();
            auto position = shapes.at(1)->GetPosition();
            //shapes.at(1)->SetPosition(position.m_x, position.m_y + change);
            shapes.at(1)->SetAngularVelocity(change);
            mHeight += change;
            if (mHeight < -1)
            {
                mRising = true;
                mTime = 0;
                mContact = false;
                shapes.at(1)->SetAngularVelocity(0);
            }
        }
    }
}

/**
 * Runs when the pipe has been hit
 * @param contact The contact listener
 */
void Pipe::BeginContact(b2Contact *contact)
{
    // Turn the Pipe active
    mContact = true;
}

/**
 * Adds the pipe as a contact listener
 */
void Pipe::AddToListener()
{
    GetMachine()->GetContactListener()->Add(GetShapes().at(1)->GetBody(), this);
}

/**
 *
 * @param x The x position of the pipe
 * @param y The y position of the pipe
 */
void Pipe::SetInitialPosition(double x, double y)
{
    Component::SetPosition(wxPoint(x, y));
    for (auto shape : GetShapes())
    {
        shape->SetPosition(x, y);
    }
}
