/**
* @file MachineSystem.cpp
 * @author Logan Bagdade
 */

#include "pch.h"
#include "MachineSystem.h"

#include "Machine.h"
#include "MachineCFactory.h"
#include "Machine1Factory.h"
#include "Machine2Factory.h"

/**
 * Constructor
 * @param resourcesDir the directory of images
 */
MachineSystem::MachineSystem(std::wstring resourcesDir) : mResourcesDir(resourcesDir)
{

    Machine1Factory factory(resourcesDir);
    std::shared_ptr<Machine> machine = factory.Create(1);
    machine->SetMachineSystem(this);
    mMachines.push_back(machine);
    mCurrentMachine = mMachines.at(0);
    mMachineNumber = 1;

    Machine2Factory factory2(resourcesDir);
    std::shared_ptr<Machine> machine2 = factory2.Create(2);
    machine2->SetMachineSystem(this);
    mMachines.push_back(machine2);

    MachineCFactory factoryC(resourcesDir);
    std::shared_ptr<Machine> machineC = factoryC.Create();
    machineC->SetMachineSystem(this);
    mMachines.push_back(machineC);

}

/**
* Set the position for the root of the machine
* @param location The x,y location to place the machine
*/
void MachineSystem::SetLocation(wxPoint location)
{
    mCurrentMachine->SetLocation(location);
}

/**
 * Get the location of hte machine
 * @return Location x,y in pixels as a point
 */
wxPoint MachineSystem::GetLocation()
{
    return mCurrentMachine->GetLocation();
}

/**
* Draw the machine at the currently specified location
* @param graphics Graphics object to render to
*/
void MachineSystem::DrawMachine(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->SetInterpolationQuality(wxINTERPOLATION_BEST);
    mCurrentMachine->Draw(graphics);
}

/**
* Set the current machine animation frame
* @param frame Frame number
*/
void MachineSystem::SetMachineFrame(int frame)
{
    if (frame < 0)
    {
        frame = 0;
    }

    if (frame < mFrame)
    {
        Reset();
    }

    for( ; mFrame < frame;  mFrame++)
    {
        mCurrentMachine->Update(1.0 / mFrameRate);
    }
}

/**
 * Set the expected frame rate in frames per second
 * @param rate Frame rate in frames per second
 */
void MachineSystem::SetFrameRate([[maybe_unused]] double rate)
{
    mFrameRate = rate;
}

/**
* Set the machine number
* @param machine An integer number. Each number makes a different machine
*/
void MachineSystem::ChooseMachine(int machine)
{
    if (machine != 1 && machine != 2 || machine == mMachineNumber)
    {
        return;
    }
    else
    {
        if (machine == 1)
        {
            mCurrentMachine = mMachines.at(0);
        }
        else if (machine == 2)
        {
            mCurrentMachine = mMachines.at(1);
        }
        mMachineNumber = machine;
        Reset();
    }
}

/**
 * Get the current machine number
 * @return Machine number integer
 */
int MachineSystem::GetMachineNumber()
{
    ///return mStandin->GetMachine();
    return 0;
}

/**
 * Get the current machine time.
 * @return Machine time in seconds
 */
double MachineSystem::GetMachineTime()
{
    return mFrame / mFrameRate;
}

/**
 * Resets the machine
 */
void MachineSystem::Reset()
{
    mFrame = 0;
    if (mMachineNumber == 1)
    {
        wxPoint location = mCurrentMachine->GetLocation();

        Machine1Factory factory(mResourcesDir);
        std::shared_ptr<Machine> machine = factory.Create(1);
        machine->SetMachineSystem(this);
        mMachines.at(0) = machine;
        mCurrentMachine = mMachines.at(0);

        mCurrentMachine->SetLocation(location);
    }
    else if (mMachineNumber == 2)
    {
        wxPoint location = mCurrentMachine->GetLocation();

        Machine2Factory factory(mResourcesDir);
        std::shared_ptr<Machine> machine = factory.Create(2);
        machine->SetMachineSystem(this);
        mMachines.at(1) = machine;
        mCurrentMachine = mMachines.at(1);

        mCurrentMachine->SetLocation(location);
    }
}
