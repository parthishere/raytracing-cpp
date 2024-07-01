
#include <fstream>

#include "camera.hpp"
#include "hittable_list.hpp"
#include "hittable.hpp"
#include "sphere.hpp"
#include "timer.hpp"

#define NDEBUG false

// point3 == color == vec3

int main()
{

  Timer timer;
  // World
  HittableList world;
  auto material_ground = make_shared<Lambertian>(color(0.8, 0.8, 0.0));
  auto material_center = make_shared<Metal>(color(0.1, 0.2, 0.5), 0.0);
  auto material_left = make_shared<Dielectric>(1.50);
  auto material_bubble = make_shared<Dielectric>(1.00 / 1.50);
  auto material_right = make_shared<Metal>(color(0.8, 0.6, 0.2), 1.0);

  world.add(make_shared<Sphere>(point3(0.0, 0.0, -1.2), 0.5, material_center));
  world.add(make_shared<Sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
  world.add(make_shared<Sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));
  world.add(make_shared<Sphere>(point3(-1.0, 0.0, -1.0), 0.4, material_bubble));
  world.add(make_shared<Sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));

  Camera cam;

  cam.aspect_ratio = 16.0 / 9.0;
  cam.image_width = 1200;
  cam.samples_per_pixel = 100;
  cam.max_depth = 50;

  cam.render(world);

  return EXIT_SUCCESS;
}
