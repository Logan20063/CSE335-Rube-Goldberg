/**
 * @file SpeedVisitor.cpp
 * @author Logan Bagdade
 */

#include "pch.h"
#include "SpeedVisitor.h"
#include "Pulley.h"

/**
 * SpeedVisitor constructor
 * @param speed How fast to set pulleys
 */
SpeedVisitor::SpeedVisitor(double speed)
{
    mSpeed = speed;
}

/**
 * Visits a pulley
 * Sets the speed of the pulley to mSpeed
 * @param pulley The pulley to visit
 */
void SpeedVisitor::VisitPulley(Pulley* pulley)
{
    pulley->SetSpeed(mSpeed);
}
