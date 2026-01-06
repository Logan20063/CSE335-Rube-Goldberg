/**
 * @file Machine2Factory.h
 * @author Logan Bagdade
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINE2FACTORY_H
#define CANADIANEXPERIENCE_MACHINE2FACTORY_H
#include <memory>

#include "Machine.h"

/**
 * Factory that creates machine #2
 */
class Machine2Factory
{
private:
    /// Path to the resources directory
    std::wstring mResourcesDir;

    /// Path to the images directory
    std::wstring mImagesDir;

public:
    Machine2Factory(std::wstring resourcesDir);

    /// Default constructor (disabled)
    Machine2Factory() = delete;

    /// Copy constructor (disabled)
    Machine2Factory(const Machine2Factory &) = delete;

    /// Assignment operator
    void operator=(const Machine2Factory &) = delete;

    std::shared_ptr<Machine> Create(int num);
};


#endif //CANADIANEXPERIENCE_MACHINE2FACTORY_H