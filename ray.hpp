#ifndef __RAY_H__
#define __RAY_H__

#include "vec3.hpp"

class Ray{
    public:
        Ray() {};

        Ray(const point3& origin, const vec3& direction) : org(origin), dir(direction) {};

        const point3& origin() const { return org; };
        const vec3& direction() const { return dir; };

        /*
        * The function implements the parametric equation of a line (or ray) in 3D space:
        *  P(t) = P₀ + t * v
        * Where:
        * P(t) is the point we're calculating (the result of this function)
        * P₀ is the origin point of the ray (orig)
        * v is the direction vector of the ray (dir)
        * t is a scalar parameter (the input to the function)
        * Breaking it down further:
        * orig represents the starting point of the ray (P₀).
        * dir represents the direction vector of the ray (v). It's typically normalized (length of 1) but doesn't have to be.
        * t is a scalar that determines how far along the ray we go.
        * If t = 0, we're at the origin of the ray.
        * If t = 1, we've gone one full length of the direction vector.
        * t can be negative (going "backwards" along the ray) or any positive number.
        * The operation orig + t*dir does the following:
        * Multiplies the direction vector by t (scaling it)
        * Adds this scaled vector to the origin point
        */
        point3 point_along_ray(double value) const {
            return org + value*dir;
        }

    private:
        point3 org;
        vec3 dir;
};

#endif