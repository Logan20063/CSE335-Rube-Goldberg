/**
 * @file MachineDrawable.cpp
 * @author Logan Bagdade
 */

#include "pch.h"
#include "MachineDrawable.h"
#include "Timeline.h"

/**
 * The MachineDrawable Constructor
 * @param resourcesDir The directory to all the images
 * @param machineNumber the machine number to set the machine system to
 */
MachineDrawable::MachineDrawable(std::wstring resourcesDir, int machineNumber) : Drawable(L"MachineSystem")
{
    MachineSystemFactory factory = MachineSystemFactory(resourcesDir);
    mMachineSystem = factory.CreateMachineSystem();
    mMachineSystem->ChooseMachine(machineNumber);
    mMachineNumber = machineNumber;
}

/**
 * Draws the MachineDrawable
 * @param graphics What to draw the MachineDrawable with
 */
void MachineDrawable::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mMachineSystem->SetMachineFrame(mTimeline->GetCurrentFrame() - 60 * (mMachineNumber - 1));
    graphics->PushState();
    graphics->Translate((float)(500 * mMachineNumber), (float)500);
    graphics->Scale((float)0.5, (float)0.5);
    mMachineSystem->DrawMachine(graphics);
    graphics->PopState();
}

/**
 * Associates a timeline with this MachineDrawable
 * @param timeline The timeline to associate with the MachineDrawable
 */
void MachineDrawable::SetTimeline(Timeline* timeline)
{
    Drawable::SetTimeline(timeline);
    mTimeline = timeline;
}

