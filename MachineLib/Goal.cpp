/**
 * @file Goal.cpp
 * @author Logan Bagdade
 */

#include "pch.h"
#include "Goal.h"

#include "Machine.h"

/// Image to draw for the goal
const std::wstring GoalImage = L"/images//goal.png";

/// Size to draw the entire goal post image
/// This does not go into the physics system at all
const auto GoalSize = wxSize(65, 247);

/// Size to create a rectangle in the physics system only
/// (does not draw) to reflect off of the backboard and post
const auto PostSize = wxSize(10, 250);

/// Size of a target object inside the goal net that
/// we'll consider a score when touched by a ball
const auto TargetSize = wxSize(20, 5);

/// The color of the scoreboard background
const auto ScoreboardBackgroundColor = wxColor(24, 69, 59);

/// Width of the black line around the scoreboard
const int ScoreboarderLineWidth = 3;

/// Scoreboard font size (height) in cm
/// The font color is white
const int ScoreboardFontSize = 20;

/// Rectangle that represents the location relative to the
/// goal position for the scoreboard and its size.
const auto ScoreboardRectangle = wxRect2DDouble(5, 280, 30, 20);

/// Location of the scoreboard text relative to the
/// scoreboard location in cm.
const auto ScoreboardTextLocation = wxPoint2DDouble(9, 280);

/// Position of the goalpost polygon relative to the entire goal
/// This plus the location set by SetPosition is where to draw
/// the goalpost PhysicsPolygon object.
const wxPoint2DDouble PostPosition = wxPoint2DDouble(22, 0);

/// Position of the basket goal polygon relative to the entire goal
/// This plus the location set by SetPosition is where to draw
/// the goalpost PhysicsPolygon object.
const wxPoint2DDouble GoalPosition = wxPoint2DDouble(-12, 165);

/**
 * Goal Constructor
 * @param imageDir The path to the directory containing images
 */
Goal::Goal(std::wstring imageDir) : Component()
{
    std::shared_ptr<cse335::PhysicsPolygon> goal = std::make_shared<cse335::PhysicsPolygon>();
    goal->SetImage(imageDir + GoalImage);
    goal->Rectangle(0, 0, GoalSize.x, GoalSize.y);
    AddShape(goal);

    std::shared_ptr<cse335::PhysicsPolygon> scoreboard = std::make_shared<cse335::PhysicsPolygon>();
    scoreboard->SetColor(wxColour(0, 0, 0));
    scoreboard->Rectangle(ScoreboardRectangle.m_x, ScoreboardRectangle.m_y, ScoreboardRectangle.m_width, ScoreboardRectangle.m_height);
    AddShape(scoreboard);

    std::shared_ptr<cse335::PhysicsPolygon> back = std::make_shared<cse335::PhysicsPolygon>();
    back->SetColor(wxColour(255, 0, 0));
    back->SetOpacity(0);
    back->Rectangle(50, PostPosition.m_y, PostSize.x, PostSize.y);
    AddShape(back);

    std::shared_ptr<cse335::PhysicsPolygon> front = std::make_shared<cse335::PhysicsPolygon>();
    front->SetColor(wxColour(255, 0, 0));
    front->SetOpacity(0);
    front->Rectangle(0, PostPosition.m_y + 150, PostSize.x, 37);
    AddShape(front);

    std::shared_ptr<cse335::PhysicsPolygon> contact = std::make_shared<cse335::PhysicsPolygon>();
    contact->SetColor(wxColour(255, 0, 0));
    contact->SetOpacity(0);
    contact->Rectangle(20, PostPosition.m_y + 160, 5, 5);
    AddShape(contact);
}

/**
 * Draws the goalpost
 * @param graphics The graphics to draw the goal with
 */
void Goal::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    Component::Draw(graphics);

    wxFont font(wxSize(0, 20),
            wxFONTFAMILY_SWISS,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL);

    wxColour color = wxColour(255, 255, 255);

    auto graphicFont = graphics->CreateFont(font, color);
    graphics->SetFont(graphicFont);
    //graphics->PushState();
    //graphics->Translate(mPosition.x + ScoreboardTextLocation.m_x,mPosition.y + ScoreboardTextLocation.m_y);
    //graphics->Scale(1, -1);
    wxPoint mPosition = GetPosition();
    //graphics->DrawText(std::to_string(mScore), ScoreboardTextLocation.m_x + location.x, ScoreboardTextLocation.m_y + location.y);
    //graphics->PopState();

    graphics->PushState();
    graphics->Translate(mPosition.x + ScoreboardTextLocation.m_x,mPosition.y + ScoreboardTextLocation.m_y + 18);
    graphics->Scale(1, -1);
    graphics->DrawText(std::to_string(mScore), 0, 0);
    graphics->PopState();
}

/**
 * Sets the position of the goal
 * @param x The x position of the goal
 * @param y The y position of the goal
 */
void Goal::SetPosition(double x, double y)
{
    Component::SetPosition(wxPoint(x, y));
    for (auto const & shape : GetShapes())
    {
        wxPoint2DDouble position = shape->GetPosition();
        shape->SetPosition(position.m_x + x, position.m_y + y);
    }
}

/**
 * Adds the goal to the world
 * @param world The world to add the goal to
 */
void Goal::SetWorld(std::shared_ptr<b2World> world)
{
    auto shapes = GetShapes();
    shapes.at(2)->InstallPhysics(world);
    shapes.at(3)->InstallPhysics(world);
    shapes.at(4)->InstallPhysics(world, true);
}

/**
 * Sets the goal as a contact listener
 */
void Goal::AddToListener()
{
    GetMachine()->GetContactListener()->Add(GetShapes().at(4)->GetBody(), this);
}

/**
 * Handle a contact beginning
 * @param contact Contact object
 */
void Goal::BeginContact(b2Contact *contact)
{
    mScore += 1;
}
