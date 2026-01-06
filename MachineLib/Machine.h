/**
 * @file Machine.h
 * @author Logan Bagdade
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINE_H
#define CANADIANEXPERIENCE_MACHINE_H
#include <memory>
#include <wx/gdicmn.h>
#include <vector>

#include "b2_world.h"
#include "MachineSystem.h"

class Component;
class ContactListener;

/**
 * The class that represents a machine
 */
class Machine
{
private:
    ///List of all components
    std::vector<std::shared_ptr<Component>> mComponents;

    ///Machine number
    int mNumber;

    ///The location of the machine
    wxPoint mLocation = wxPoint(0,0);

    ///The physics world
    std::shared_ptr<b2World> mWorld;

    /// The installed contact filter
    std::shared_ptr<ContactListener> mContactListener;

    ///The machine System
    MachineSystem* mMachineSystem = nullptr;

public:
    Machine(int number);

    void Update(double elapsed);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);
    void AddComponent(std::shared_ptr<Component> pComponent);
    void SetLocation(wxPoint pLocation);
    void Reset();
    wxPoint GetLocation();
    std::shared_ptr<b2World> GetWorld();

    /**
     * Links a machineSystem with this machine
     * @param pMachineSystem the machine system to link to
     */
    void SetMachineSystem(MachineSystem* pMachineSystem) { mMachineSystem = pMachineSystem; }

    /**
     * Returns mContactListener
     * @return the contact listener of the machine
     */
    std::shared_ptr<ContactListener> GetContactListener() { return mContactListener; }
};


#endif //CANADIANEXPERIENCE_MACHINE_H