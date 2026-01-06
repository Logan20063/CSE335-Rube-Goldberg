/**
 * @file Pulley.h
 * @author Logan Bagdade
 *
 *
 */

#ifndef CANADIANEXPERIENCE_PULLEY_H
#define CANADIANEXPERIENCE_PULLEY_H

#include "Component.h"
#include "ISink.h"
#include "ISinkVisitor.h"
#include "Source.h"

/**
 * The pulley component of the machine
 */
class Pulley : public Component, public ISink
{
private:
    ///The source component of this pulley
    std::shared_ptr<Source> mSource = nullptr;

    ///The source of this pulley
    Pulley* mSourcePulley = nullptr;

    ///The pulleys this pulley drives
    std::vector<std::shared_ptr<Pulley>> mPulleies;

    ///The radius of the pulley
    double mRadius;

    ///The speed of the pulley
    double mSpeed = 0;

public:
    Pulley(double radius);

    void SetImage(std::wstring path);

    void SetPosition(wxPoint position);
    void SetPosition(double x, double y);

    void SetWorld(std::shared_ptr<b2World> world) override;

    void Rotate(double rotation) override;

    void Drive(std::shared_ptr<Pulley> pulley);

    void SetSource(Pulley*);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * Returns the radius of the pulley
     * @return The radius of the pulley
     */
    double GetRadius() { return mRadius; }

    /**
     * Returns the source class associated with this pulley
     * @return The sourc part of this pulley
     */
    std::shared_ptr<Source> GetSource() { return mSource; }

    void Update(double elapsed) override;

    /**
     * Accepts a visitor
     * @param visitor The visitor to accept
     */
    void Accept(ISinkVisitor* visitor) override { visitor->VisitPulley(this); }

    /**
     * Sets the speed of the pulley
     * @param speed The new speed of the pulley
     */
    void SetSpeed(double speed) { mSpeed = speed; }
};


#endif //CANADIANEXPERIENCE_PULLEY_H