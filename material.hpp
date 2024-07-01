#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "macros.hpp"
#include "hittable.hpp"

class Material
{
public:
    virtual ~Material() = default;

    virtual bool scatter(const Ray &ray_in, const HitRecord &record, color &attenuation, Ray &scattered_ray) const
    {
        return false;
    }

private:
};

class Lambertian : public Material
{
public:
    Lambertian(const color &albedo) : albedo(albedo) {}

    bool scatter(const Ray &ray_in, const HitRecord &record, color &attenuation, Ray &scattered_ray)
        const override
    {
        // vec3 direction = random_on_hemisphere(record.normal);
        auto scattering_direction = record.normal + random_unit_vector();

        // Catch degenerate scatter direction
        if (scattering_direction.near_zero())
            scattering_direction = record.normal;

        scattered_ray = Ray(record.point, scattering_direction);
        attenuation = albedo;
        return true;
    }

private:
    color albedo;
};


class Metal : public Material {
  public:
    Metal(const color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

    bool scatter(const Ray &ray_in, const HitRecord &record, color &attenuation, Ray &scattered_ray)
        const override
    {
        vec3 reflected = reflect(ray_in.direction(), record.normal);
        
        // If a and b represent displacements, their sum c is the total displacement.
        reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
        scattered_ray = Ray(record.point, reflected);
        attenuation = albedo;

        return (dot(scattered_ray.direction(), record.normal) > 0);
    }

  private:
    color albedo;
    double fuzz;
};

#endif