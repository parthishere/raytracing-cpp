
#include <fstream>

#include "camera.hpp"
#include "hittable_list.hpp"
#include "hittable.hpp"
#include "sphere.hpp"

#define NDEBUG false

// point3 == color == vec3




int main()
{

  // World
  HittableList world;
  world.add(make_shared<Sphere>(point3(0,0,-1), 0.5));
  world.add(make_shared<Sphere>(point3(0,-100.5,-1), 100));

  Camera cam;

  cam.aspect_ratio = 16.0 / 9.0;
  cam.image_width  = 400;
  cam.samples_per_pixel = 1000;

  cam.render(world);

  return EXIT_SUCCESS;
}
