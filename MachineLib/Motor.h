/**
 * @file Motor.h
 * @author Logan Bagdade
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MOTOR_H
#define CANADIANEXPERIENCE_MOTOR_H

#include "b2_world_callbacks.h"
#include "Component.h"
#include "Source.h"

/**
 * A class for the motor component of the machine
 */
class Motor : public Component, public b2ContactListener
{
private:
    ///Whether the motor is idle or not
     bool mIsActive = false;

    ///The speed of the motor
    double mSpeed = 0;

    ///The amount of frames this motor has been active
    double mActiveFrames = 0;

    ///The directory to images
    std::wstring mImagesDir;

    ///The source of the motor
    std::shared_ptr<Source> mSource = nullptr;

    /// Is this motor oscillating?
    bool mOscillating = false;

    /// Maximum oscillation spread
    double mSpread = 0.1;

    /// Windup to launch speed ratio
    double mWindupToReleaseRatio = 5.0;

    ///Whether the motor is going forward
    bool mForward = true;

public:
    Motor(std::wstring imageDir);

    void SetPosition(double x, double y);

    void SetWorld(std::shared_ptr<b2World> world) override;

     /**
      * Sets whether motor is idle or not
      * @param active Whether the motor starts active
      */
     void SetInitiallyActive(bool active) { mIsActive = active; }

    /**
     * Sets the speed of the motor
     * @param speed The speed to set the motor to
     */
    void SetSpeed(double speed) { mSpeed = speed; }

    void Update(double elapsed) override;

    void BeginContact(b2Contact *contact) override;

    void AddToListener();

    wxPoint GetShaftPosition();

    /**
     * Returns the source of this motor
     * @return The source associated with this motor
     */
    std::shared_ptr<Source> GetSource() { return mSource; }

    /**
     * Sets whether the motor oscilates or not
     * @param o Whether to set the motor to oscillate
     */
    void SetOscillating(bool o) { mOscillating = o; }

    /**
     * Sets the spread of the motor
     * @param spread The new spread of the motor
     */
    void SetSpread(double spread) { mSpread = spread; }

    /**
     * Sets the ratio between the windup and release of the motor
     * @param ratio The new ratio
     */
    void SetWindupToReleaseRatio(double ratio) { mWindupToReleaseRatio = ratio; }
};


#endif //CANADIANEXPERIENCE_MOTOR_H