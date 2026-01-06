/**
 * @file Machine2Factory.cpp
 * @author Logan Bagdade
 */

#include "pch.h"
#include "Machine2Factory.h"
#include "Machine.h"
#include "Shape.h"
#include "Motor.h"
#include "Goal.h"
#include "Pipe.h"
#include "Conveyor.h"
#include "Pulley.h"

/// The images directory in resources
const std::wstring ImagesDirectory = L"/images";

/**
 * Constructor
 * @param resourcesDir Directory containing the machine resources
 */
Machine2Factory::Machine2Factory(std::wstring resourcesDir) :mResourcesDir(resourcesDir)
{
    mImagesDir = resourcesDir + ImagesDirectory;
}

/**
 * Create a machine
 * @param num The machine number
 * @return Pointer to newly created machine
 */
std::shared_ptr<Machine> Machine2Factory::Create(int num)
{
    auto machine = std::make_shared<Machine>(num);

    const double FloorWidth = 600;
    const double FloorHeight = 15;

    auto floor = std::make_shared<Shape>();
    floor->Rectangle(-FloorWidth/2, -FloorHeight, FloorWidth, FloorHeight);
    floor->SetImage(mImagesDir + L"/floor.png");
    floor->SetInitialPosition(0, -40);
    machine->AddComponent(floor);

    auto basketball = std::make_shared<Shape>();
    basketball->Circle(16);
    basketball->SetImage(mImagesDir + L"/basketball.png");
    basketball->SetInitialPosition(-50, 352);
    basketball->SetDynamic();
    basketball->SetPhysics(1, 0.5, 0.5);
    machine->AddComponent(basketball);

    auto basketball2 = std::make_shared<Shape>();
    basketball2->Circle(16);
    basketball2->SetImage(mImagesDir + L"/basketball.png");
    basketball2->SetInitialPosition(70, 400);
    basketball2->SetDynamic();
    basketball2->SetPhysics(1, 0.5, 0.5);
    machine->AddComponent(basketball2);

    auto goal = std::make_shared<Goal>(mResourcesDir);
    goal->SetPosition(50, -40);
    machine->AddComponent(goal);
    goal->AddToListener();

    auto pipe = std::make_shared<Pipe>(mResourcesDir);
    pipe->SetInitialPosition(-20, -40);
    machine->AddComponent(pipe);
    pipe->AddToListener();

    auto wedgeEC = std::make_shared<Shape>();
    wedgeEC->AddPoint(-25, 0);
    wedgeEC->AddPoint(25, 0);
    wedgeEC->AddPoint(25, 4.5);
    wedgeEC->AddPoint(-25, 55);
    wedgeEC->SetImage(mImagesDir + L"/wedge.png");
    wedgeEC->SetInitialRotation(0.25);
    wedgeEC->SetInitialPosition(100, 50);
    machine->AddComponent(wedgeEC);

    auto motorEC = std::make_shared<Motor>(mImagesDir);
    motorEC->SetPosition(-280, 340);
    motorEC->SetInitiallyActive(true);      // Initially active
    motorEC->SetSpeed(.4);
    machine->AddComponent(motorEC);
    auto motorECshaft = motorEC->GetShaftPosition();

    auto conveyorEC = std::make_shared<Conveyor>(mImagesDir);
    conveyorEC->SetPosition(-50, 320);
    machine->AddComponent(conveyorEC);
    auto conveyorECshaft = conveyorEC->GetShaftPosition();

    auto pulleyMotorEC = std::make_shared<Pulley>(10);
    pulleyMotorEC->SetImage(mImagesDir + L"/pulley.png");
    pulleyMotorEC->SetPosition(motorECshaft);
    machine->AddComponent(pulleyMotorEC);

    motorEC->GetSource()->AddSink(pulleyMotorEC);

    auto pulleyConveyorEC = std::make_shared<Pulley>(10);
    pulleyConveyorEC->SetImage(mImagesDir + L"/pulley2.png");
    pulleyConveyorEC->SetPosition(conveyorECshaft);
    machine->AddComponent(pulleyConveyorEC);

    pulleyMotorEC->Drive(pulleyConveyorEC);
    pulleyConveyorEC->GetSource()->AddSink(conveyorEC);

    return machine;
}
