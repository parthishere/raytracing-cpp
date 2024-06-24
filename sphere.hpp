#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.hpp"

class sphere : public Hittable {
    public:
        sphere(const point3& center, double radius) : center(center), radius(fmax(0,radius)) {}

        bool hit(const Ray& ray, double ray_along_distance_t_min, double ray_along_distance_t_max, HitRecord& record) const override {

            vec3 c_q = center - ray.origin();

            double a = ray.direction().value_squared();
            double h = dot(ray.direction(), c_q);
            double c = c_q.value_squared() - (radius * radius);

            double delta = (h * h) - (a * c);

            if (delta < 0)
                return false;

            double sqrt_delta = sqrt(delta);

            double root = ((h - sqrt_delta) / a);   
            if (root <= ray_along_distance_t_min || root >= ray_along_distance_t_max ) {
                root = ((h - sqrt_delta) / a);
                if(root <= ray_along_distance_t_min || root >= ray_along_distance_t_max ){
                    return false;
                }
            }

            record.distance = root;
            record.point = ray.point_along_ray(record.distance);
            record.normal = (record.point - center) / radius;  //unit vector

            return true;
        }

    private:
        point3 center;
        double radius;
};



#endif