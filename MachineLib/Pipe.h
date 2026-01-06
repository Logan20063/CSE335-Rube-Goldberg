/**
 * @file Pipe.h
 * @author Logan Bagdade
 *
 *
 */

#ifndef CANADIANEXPERIENCE_PIPE_H
#define CANADIANEXPERIENCE_PIPE_H
#include "b2_world_callbacks.h"
#include "Component.h"

/**
 * The pipe component of the machine
 */
class Pipe : public Component, public b2ContactListener
{
private:
    ///The height of the bottom
    double mHeight = 0;

    ///Whether the bottom is rising or not
    bool mRising = true;

    ///Time since contact
    double mTime = 0;

    ///Whether the pipe is in contact
    bool mContact = false;

public:
    Pipe(std::wstring imageDir);
    virtual ~Pipe() = default;

    void SetWorld(std::shared_ptr<b2World> world) override;
    void Update(double elapsed) override;
    void BeginContact(b2Contact* contact);
    void AddToListener();
    void SetInitialPosition(double x, double y);
};


#endif //CANADIANEXPERIENCE_PIPE_H