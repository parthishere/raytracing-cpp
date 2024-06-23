#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public Hittable {
    public:
        sphere(const point3& center, double radius) : center(center), radius(fmax(0,radius)) {}

    private:
        point3 center;
        double radius;
};



#endif