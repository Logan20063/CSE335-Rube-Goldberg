/**
 * @file MachineDrawable.h
 * @author Logan Bagdade
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINEDRAWABLE_H
#define CANADIANEXPERIENCE_MACHINEDRAWABLE_H
#include "Drawable.h"
#include <machine-api.h>
#include <memory>

/**
 * the subclass to draw a machine system
 */
class MachineDrawable : public Drawable
{
private:
    ///The machine system associated with this MachineDrawable
    std::shared_ptr<IMachineSystem> mMachineSystem;

    ///The timeline associated with the MachineDrawable
    Timeline* mTimeline;

    ///The machine this MachineDrawable is set to draw
    int mMachineNumber;

public:
    MachineDrawable(std::wstring resourcesDir, int machineNumber);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     *
     * @param pos Position being hit tested
     * @return false
     */
    bool HitTest(wxPoint pos) override { return false;}

    void SetTimeline(Timeline* timeline) override;
};


#endif //CANADIANEXPERIENCE_MACHINEDRAWABLE_H