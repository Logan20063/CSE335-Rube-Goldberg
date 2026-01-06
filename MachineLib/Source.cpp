/**
 * @file Source.cpp
 * @author Logan Bagdade
 */

#include "pch.h"
#include "Source.h"
#include "SpeedVisitor.h"

/**
 * Rotates all the sinks associated with the source
 * @param elapsed How long it's been since the last update
 */
void Source::RotateAll(double elapsed)
{
    for (std::shared_ptr<ISink> sink : mSinks)
    {
        sink->Rotate(mRotation * elapsed);
    }
}

/**
 * Sets the speed of all pulleys associated with the source
 */
void Source::SetPulleySpeed()
{
    SpeedVisitor visitor(mRotation);
    for (std::shared_ptr<ISink> sink : mSinks)
    {
        sink->Accept(&visitor);
    }
}
