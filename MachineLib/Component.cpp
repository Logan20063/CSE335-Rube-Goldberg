/**
 * @file Component.cpp
 * @author Logan Bagdade
 */

#include "pch.h"
#include "Component.h"

/**
 * Draws the component onto the screen
 * @param graphics What's used to draw the component
 */
void Component::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    for (std::shared_ptr<cse335::PhysicsPolygon> polygon : mShapes)
    {
        polygon->Draw(graphics);
    }
}
