#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.hpp"
#include "interval.hpp"

class Sphere : public Hittable {
    public:
        Sphere(const point3& center, double radius, shared_ptr<Material> material) : center(center), radius(fmax(0,radius)), material(material) {}

        bool hit(const Ray& ray, Interval ray_t, HitRecord& record) const override {

            vec3 c_q = center - ray.origin();

            double a = ray.direction().value_squared();
            double h = dot(ray.direction(), c_q);
            double c = c_q.value_squared() - (radius * radius);

            double delta = (h * h) - (a * c);

            if (delta < 0)
                return false;

            double sqrt_delta = sqrt(delta);

            double root = ((h - sqrt_delta) / a);   
            if (!ray_t.surrounds(root)) {
                root = ((h - sqrt_delta) / a);
                if(!ray_t.surrounds(root)){
                    return false;
                }
            }

            record.distance = root;
            record.point = ray.point_along_ray(record.distance);
            record.normal = (record.point - center) / radius;  //unit vector
            record.material = material;

            return true;
        }

    private:
        point3 center;
        double radius;
        std::shared_ptr<Material> material;
};



#endif