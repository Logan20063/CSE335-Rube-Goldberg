/**
 * @file Pulley.cpp
 * @author Logan Bagdade
 */

#include "pch.h"
#include "Pulley.h"

/**
 * The constructor for the pulley
 * @param radius The radius of the pulley
 */
Pulley::Pulley(double radius)
{
    std::shared_ptr<cse335::PhysicsPolygon> pulley = std::make_shared<cse335::PhysicsPolygon>();
    pulley->Circle(radius);
    AddShape(pulley);

    mSource = std::make_shared<Source>();
    mRadius = radius;
}

/**
 * Sets the image of the pulley
 * @param path The path to the image of the pulley
 */
void Pulley::SetImage(std::wstring path)
{
    GetShapes().at(0)->SetImage(path);
}

/**
 * Sets the position of the pulley
 * @param position The position of the pulley
 */
void Pulley::SetPosition(wxPoint position)
{
    Component::SetPosition(position);
    GetShapes().at(0)->SetInitialPosition(position.x, position.y);
}

/**
 * Sets the position of the pulley
 * @param x The x position of the pulley
 * @param y The y position of the pulley
 */
void Pulley::SetPosition(double x, double y)
{
    Component::SetPosition(wxPoint(x, y));
    GetShapes().at(0)->SetInitialPosition(x, y);
}

/**
 *Adds the pulley to the world
 * @param world The world to add the pulley to
 */
void Pulley::SetWorld(std::shared_ptr<b2World> world)
{

}

/**
 * Rotates a pulley
 * @param rotation The amount to rotate the pulley by
 */
void Pulley::Rotate(double rotation)
{
    if (mSourcePulley)
    {
        GetShapes().at(0)->SetRotation(GetShapes().at(0)->GetRotation() + rotation * mSourcePulley->GetRadius() / mRadius);
    }
    else
    {
        GetShapes().at(0)->SetRotation(GetShapes().at(0)->GetRotation() + rotation);
    }
}

/**
 * Links two pulleys to let pulley act like a source
 * @param pulley The pulley to link this pulley with
 */
void Pulley::Drive(std::shared_ptr<Pulley> pulley)
{
    mPulleies.push_back(pulley);
    pulley->SetSource(this);
    mSource->AddSink(pulley);
}

/**
 * Sets a source to the pulley
 * @param pulley The pulley to set as the source of this pully
 */
void Pulley::SetSource(Pulley* pulley)
{
    mSourcePulley = pulley;
}

/**
 * Draws the pulleys and belts
 * @param graphics What to draw the pulleys with
 */
void Pulley::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    wxPen black = wxPen(wxColour(0, 0, 0));
    graphics->SetPen(wxPen(black));

    for (std::shared_ptr<Pulley> const & pulley : mPulleies)
    {
        wxPoint loc1 = GetPosition();
        wxPoint loc2 = pulley->GetPosition();

        double theta = atan2(loc2.y - loc1.y, loc2.x - loc1.x);

        double r1 = GetRadius() - 3;
        double r2 = pulley->GetRadius() - 3;

        double diff1 = (loc1.x - loc2.x);
        double diff2 = (loc1.y - loc2.y);
        double magnitude = sqrt((diff1 * diff1) + (diff2 * diff2));

        double phi = asin((r2-r1)/magnitude);

        double beta = theta + phi + (M_PI / 2);
        graphics->StrokeLine(loc1.x + r1 * cos(beta), loc1.y + r1 * sin(beta), loc2.x + r2 * cos(beta), loc2.y + r2 * sin(beta));

        beta = theta - phi - (M_PI / 2);
        graphics->StrokeLine(loc1.x + r1 * cos(beta), loc1.y + r1 * sin(beta), loc2.x + r2 * cos(beta), loc2.y + r2 * sin(beta));

    }
    Component::Draw(graphics);
}

/**
 * Updates the pulley
 * @param elapsed How long it's been since the last update
 */
void Pulley::Update(double elapsed)
{
    mSource->SetRotation(mSpeed);
    mSource->RotateAll(elapsed);
    mSource->SetPulleySpeed();
}
