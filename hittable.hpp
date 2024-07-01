#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.hpp"


class Material;


class HitRecord {
    public:
        point3 point;
        vec3 normal;
        double distance;
        std::shared_ptr<Material> material;
        bool hit_on_front_face;

    void set_hit_on_front_face(const Ray& ray, const vec3& outward_normal){
        hit_on_front_face = dot(outward_normal, ray.direction()) < 0.0;
        normal = hit_on_front_face ? outward_normal : -outward_normal; 
    }
};

class Hittable {
    public:
        virtual ~Hittable() = default;

        virtual bool hit(const Ray& r, Interval ray_t, HitRecord& record) const = 0;
    
};

#endif