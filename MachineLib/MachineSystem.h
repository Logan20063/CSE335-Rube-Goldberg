/**
 * @file MachineSystem.h
 * @author Logan Bagdade
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINESYSTEM_H
#define CANADIANEXPERIENCE_MACHINESYSTEM_H

#include "IMachineSystem.h"
#include <vector>

class Machine;

/**
 * Class representing the machine system
 */
class MachineSystem : public IMachineSystem
{
private:
    ///A vector of all machines
    std::vector<std::shared_ptr<Machine>> mMachines;

    ///Pointer to current machine
    std::shared_ptr<Machine> mCurrentMachine;

    ///The frame of the machine
    int mFrame = 0;

    ///The current Machine Number
    int mMachineNumber = 2;

    ///The Frame Rate
    double mFrameRate = 30;

    ///The resources directory
    std::wstring mResourcesDir;
public:
    /// Constructor
    MachineSystem(std::wstring resourcesDir);

    /// Copy constructor (disabled)
    MachineSystem(const MachineSystem &) = delete;

    /// Assignment operator
    void operator=(const MachineSystem &) = delete;

    virtual void SetLocation(wxPoint location) override;
    virtual wxPoint GetLocation() override;

    virtual void DrawMachine(std::shared_ptr<wxGraphicsContext> graphics) override;
    virtual void SetMachineFrame(int frame) override;
    virtual void SetFrameRate(double rate) override;
    virtual void ChooseMachine(int machine) override;
    virtual int GetMachineNumber() override;
    virtual double GetMachineTime() override;
    void Reset();

    // /**
    //  * Gets the frame rate of the current machine
    //  * @return The framerate of the current machine
    //  */
    // double GetFrameRate() { return mFrameRate; }
    //
    // /**
    //  * Returns the current frame of the machine
    //  * @return The current frame of the machine
    //  */
    // int GetFrame() { return mFrame; }

    /**
     * Set the flag from the control panel
     * @param flag Flag to set
     */
    virtual void SetFlag(int flag) override{}
};


#endif //CANADIANEXPERIENCE_MACHINESYSTEM_H