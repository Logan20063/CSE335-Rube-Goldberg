/**
 * @file Goal.h
 * @author Logan Bagdade
 *
 *
 */

#ifndef CANADIANEXPERIENCE_GOAL_H
#define CANADIANEXPERIENCE_GOAL_H
#include "Component.h"
#include "ContactListener.h"


/**
 * The goal component of the machine
 */
class Goal : public Component, public b2ContactListener
{
private:
    ///The current score of the goal
    int mScore = 0;

public:
    Goal(std::wstring imageDir);
    ~Goal()=default;

    ///Override for set world function, does nothing
    void SetWorld(std::shared_ptr<b2World> world) override;
    void AddToListener();
    void BeginContact(b2Contact* contact);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void SetPosition(double x, double y);
};


#endif //CANADIANEXPERIENCE_GOAL_H