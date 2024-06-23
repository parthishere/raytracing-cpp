#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

class HitRecord {
    public:
        point3 p;
        vec3 normal;
        double distance;
};

class Hittable {
    public:
        virtual ~Hittable() = default;

        virtual bool hit(const ray& r, double ray_tmin, double ray_tmax, HitRecord& rec) const = 0;
    
};

#endif