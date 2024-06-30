#pragma once

#include <random>
#include <chrono>
#include <cstdlib>

class Random
{
public:
    Random(double min, double max) :min(min), max(max), rgb(min, max) {}

    Random(): min(0.0), max(1.0), rgb(0.0, 1.0) {};


    double random() {
        return rgb(mt);
    }

    vec3 sample_square() {
        // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
        return vec3(random() - 0.5, random() - 0.5, 0);
    }
    
private:
    double min, max;
    std::random_device rd; 
    std::seed_seq ss{(static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count())), rd(), rd(), rd(), rd(), rd()};
    std::mt19937 mt{ss};
    std::uniform_real_distribution<> rgb;
};
