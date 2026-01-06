/**
 * @file Source.h
 * @author Logan Bagdade
 *
 *
 */

#ifndef CANADIANEXPERIENCE_SOURCE_H
#define CANADIANEXPERIENCE_SOURCE_H

#include "ISink.h"
#include <vector>

/**
 * A class to represent sources
 * Sources take in sinks and rotate them
 */
class Source
{
private:
    /// The rotation of the source
    double mRotation = 0;

    ///A vector of the sinks linksed to this source
    std::vector<std::shared_ptr<ISink>> mSinks;
public:
    /**
     * Sets the rotation of the source
     * @param rotation The rotation to set the source to
     */
    void SetRotation(double rotation) { mRotation = rotation; }

    /**
     * Gets the rotation of the source
     * @return The rotation of the source
     */
    double GetRotation() const { return mRotation; }

    /**
     * Links a sink with this source
     * @param sink The sink to link to this source
     */
    void AddSink(std::shared_ptr<ISink> sink) { mSinks.push_back(sink); }

    void RotateAll(double elapsed);

    void SetPulleySpeed();
};


#endif //CANADIANEXPERIENCE_SOURCE_H