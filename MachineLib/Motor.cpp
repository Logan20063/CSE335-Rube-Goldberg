/**
 * @file Motor.cpp
 * @author Logan Bagdade
 */

#include "pch.h"
#include "Motor.h"
#include "ContactListener.h"
#include "Machine.h"

/// The center point for drawing the wheel
/// relative to the bottom center of the box
const auto WheelCenter = wxPoint2DDouble(-12, 24);

/// The size of the motor box in centimeters
const auto MotorBoxSize = wxSize(75, 50);

/// Size of the motor wheel (diameter) in centimeters
const double MotorWheelSize = 45;

/// Size of the motor wheel (square) in centimeters
const double MotorSize = 45;

/// How fast the motor runs. This is how many cycles of
/// the 3 images we make per revolution of the wheel
/// as images 1, 2, 3, 2, ... The value of 4.0 means
/// 4 complete cycles per resolution, one image every 1/16
/// of a revolution
const double MotorSpeed = 4.0;

/// The offset from the bottom center of the motor box
/// to the center of the output shaft.
const auto MotorShaftOffset = wxPoint2DDouble(25, 40);

/// The image for the motor box
const std::wstring MotorBoxImage = L"/motor-box.png";

/// The image for the motor wheel
const std::wstring MotorWheelImage = L"/wheel.png";

/// The motor images. Image 0 is idling, 1-8 are
/// the active motor animation images.
const std::wstring MotorImages[5] =
{L"/motor-idle.png", L"/motor-active-1.png",
    L"/motor-active-2.png", L"/motor-active-3.png",
    L"/motor-active-4.png"};

/**
 * Motor constructor
 * @param imageDir The directory to the image directory
 */
Motor::Motor(std::wstring imageDir) : Component()
{
    mImagesDir = imageDir;

    std::shared_ptr<cse335::PhysicsPolygon> box = std::make_shared<cse335::PhysicsPolygon>();
    box->BottomCenteredRectangle(MotorBoxSize);
    box->SetColor(wxColour(99, 185, 157));
    AddShape(box);

    std::shared_ptr<cse335::PhysicsPolygon> outsideBox = std::make_shared<cse335::PhysicsPolygon>();
    outsideBox->BottomCenteredRectangle(MotorBoxSize);
    outsideBox->SetImage(imageDir + MotorBoxImage);
    AddShape(outsideBox);

    std::shared_ptr<cse335::PhysicsPolygon> wheel = std::make_shared<cse335::PhysicsPolygon>();
    wheel->Circle(MotorWheelSize / 2);
    wheel->SetImage(imageDir + MotorWheelImage);
    AddShape(wheel);

    std::shared_ptr<cse335::PhysicsPolygon> guy = std::make_shared<cse335::PhysicsPolygon>();
    guy->Circle(MotorSize / 2);
    guy->SetImage(imageDir + MotorImages[0]);
    AddShape(guy);

    mSource = std::make_shared<Source>();
}

/**
 * Sets the location of the motor
 * @param x The x position of the motor
 * @param y The y position of the motor
 */
void Motor::SetPosition(double x, double y)
{
    Component::SetPosition(wxPoint(x, y));
    for (int i=0; i < 4; i++)
    {
        std::shared_ptr<cse335::PhysicsPolygon> shape = GetShapes().at(i);
        switch (i)
        {
            case 0:
            case 1:
                shape->SetInitialPosition(x, y);
                break;
            case 2:
            case 3:
                shape->SetInitialPosition(x + WheelCenter.m_x, y + WheelCenter.m_y);
                break;
        }
    }
}

/**
 * Sets a world to the motor
 * @param world The world to put the motor in
 */
void Motor::SetWorld(std::shared_ptr<b2World> world)
{
    GetShapes().at(0)->InstallPhysics(world);
}

/**
 * Updates the motor
 * @param elapsed How long has passed
 */
void Motor::Update(double elapsed)
{
    if (mIsActive)
    {
        if (mOscillating)
        {
            if (mForward)
            {
                mActiveFrames += elapsed;
                if (mActiveFrames >= mSpread * mSpeed * 15)
                {
                    //mActiveFrames = mSpread;
                    mForward = false;
                }
            }
            else
            {
                mActiveFrames -= elapsed * mWindupToReleaseRatio;
                if (mActiveFrames <= 0)
                {
                    //mActiveFrames = 0;
                    mForward = true;
                }
            }
        }
        else
        {
            mActiveFrames += elapsed;
        }
        int frame = ((int)(mActiveFrames * mSpeed * 15) % 4) + 1;
        std::shared_ptr<cse335::PhysicsPolygon> guy = std::make_shared<cse335::PhysicsPolygon>();
        guy->Circle(MotorSize / 2);
        guy->SetImage(mImagesDir + MotorImages[frame]);
        wxPoint origin = GetPosition();
        guy->SetPosition(origin.x + WheelCenter.m_x, origin.y + WheelCenter.m_y);
        GetShapes().at(3) = guy;

        GetShapes().at(2)->SetRotation(mActiveFrames * mSpeed);

        if (!mForward)
        {
            mSource->SetRotation(mSpeed * mWindupToReleaseRatio * -1);
        }
        else
        {
            mSource->SetRotation(mSpeed);
        }
        mSource->RotateAll(elapsed);
        mSource->SetPulleySpeed();
    }

}

/**
 * Handle a contact beginning
 * @param contact Contact object
 */
void Motor::BeginContact(b2Contact *contact)
{
    // Turn the motor active
    mIsActive = true;
}

/**
 * Adds the motor to the contact listener
 */
void Motor::AddToListener()
{
    GetMachine()->GetContactListener()->Add(GetShapes().at(0)->GetBody(), this);
}

/**
 * Gets the location of the shaft of the motor
 * @return The position a pulley connected to this Motor should go
 */
wxPoint Motor::GetShaftPosition()
{
    return wxPoint(GetPosition().x + MotorShaftOffset.m_x, GetPosition().y + MotorShaftOffset.m_y);
}
