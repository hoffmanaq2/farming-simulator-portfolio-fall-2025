#pragma once

#include <string>

class Plot {
public:
    virtual std::string symbol() = 0;
    virtual void end_day() {
        //no-op
    }
    // whether this plot contains a mature (harvestable) plant
    virtual bool is_mature() const {
        return false;
    }
    // watering action for this plot (no-op for soil)
    virtual void water() {
        // no-op by default
    }
    virtual ~Plot() = default;
};