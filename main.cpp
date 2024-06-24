#include <cstdlib>
#include <random>
#include <chrono>
#include <fstream>

#include "camera.hpp"
#include "hittable_list.hpp"
#include "hittable.hpp"
#include "sphere.hpp"

#define NDEBUG false

// point3 == color == vec3

std::random_device rd{};
std::seed_seq ss{
    static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()),
    rd(), rd(), rd(), rd(), rd(), rd()};
std::mt19937 mt{ss};

std::uniform_int_distribution rgb{0, 255};


int main()
{

  // World
  HittableList world;
  world.add(make_shared<Sphere>(point3(0,-100.5,-1), 100));
  world.add(make_shared<Sphere>(point3(0,0,-1), 0.5));

  Camera cam;

  cam.aspect_ratio = 16.0 / 9.0;
  cam.image_width  = 400;

  cam.render(world);

  return EXIT_SUCCESS;
}
