#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "macros.hpp"

class HitRecord;

class Material{
    public:
    virtual ~Material() = default;

    virtual bool scatter(const Ray& ray_in, const HitRecord& record, color& attenuation, Ray& scattered_ray) const {
        return false;
    }
    private:
};

#endif