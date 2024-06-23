#include <iostream>
#include <cstdlib>
#include <random>
#include <chrono>
#include <fstream>

#include "vec3.h"
#include "color.h"
#include "ray.h"

#define NDEBUG false


// point3 == color == vec3

std::random_device rd{};
std::seed_seq ss{
    static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()),
    rd(), rd(), rd(), rd(), rd(), rd()};
std::mt19937 mt{ss};

std::uniform_int_distribution rgb{0, 255};


bool hit_sphere(const point3& center, const ray& ray, double radius){
  vec3 c_q = center - ray.origin();

  double a = dot(ray.direction(),ray.direction());
  double b = -2.0 * dot(ray.direction(), c_q);
  double c = dot(c_q, c_q) - (radius*radius);

  double delta = (b*b) - (4*a*c);

  return (delta >= 0);
}



color ray_color(const ray &r)
{
  if (hit_sphere(point3(0,0,-1), r, 0.5))
        return color(1, 0, 0);


  vec3 unit_direction = unit_vector(r.direction());
  auto a = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main()
{
  std::ofstream outputFile("output.ppm", std::ios::out | std::ios::trunc);

  int image_width{400};
  double aspect_ratio{16.0 / 9.0};

  int image_height = image_width / aspect_ratio;
  image_height = image_height < 1 ? 1 : image_height;

  double focal_length{1.0};
  point3 camera_center{0, 0, 0};

  double viewport_height{2.0};
  //  I have not used aspect ratio as when computing viewport_width, it's because the value set to aspect_ratio is the ideal ratio, it may not be the actual ratio between image_width and image_height. If image_height was allowed to be real valued—rather than just an integer—then it would be fine to use aspect_ratio. But the actual ratio between image_width and image_height can vary based on two parts of the code. First, image_height is rounded down to the nearest integer, which can increase the ratio. Second, we don't allow image_height to be less than one, which can also change the actual aspect ratio.
  double viewport_width = viewport_height * (double(image_width) / image_height);

  // Calculate the vectors across the horizontal and down the vertical viewport edges.
  vec3 viewport_x_vec{viewport_width, 0, 0};
  vec3 viewport_y_vec{0, -viewport_height, 0};

  // Calculate the horizontal and vertical delta vectors from pixel to pixel.
  vec3 pixel_delta_x = viewport_x_vec / image_width;
  vec3 pixel_delta_y = viewport_y_vec / image_height;

  // Calculate the location of the upper left pixel.
  point3 viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_x_vec / 2 + ((-1 * viewport_y_vec) / 2);
  point3 pixel00_loc = viewport_upper_left + (0.5 * (pixel_delta_x + pixel_delta_y));

  // render
  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
  if (outputFile.is_open())
  {
    outputFile << "P3\n" << image_width << ' ' << image_height << "\n255\n";
  }

  for (int i = 0; i < image_height; i++)
  {
    std::clog << "\rScanlines remaining: " << (image_height - i) << ' ' << std::flush;
    for (int j = 0; j < image_width; j++)
    {
      point3 pixel_center = pixel00_loc + (i * pixel_delta_y) + (j * pixel_delta_x);
      vec3 ray_direction = pixel_center - camera_center;

      ray r(camera_center, ray_direction);

      // vec3 pixel_color = vec3(rgb(mt), rgb(mt), rgb(mt)); // random pixels
      vec3 pixel_color = ray_color(r);

      if (outputFile.is_open())
      {
        // write_color(std::cout, pixel_color);
        write_color(outputFile, pixel_color);
      }
    }
  }
  outputFile.close();
  // std::cout << "Hellow world! " << std::endl;
  std::clog << "\rDone.                 \n";
  return EXIT_SUCCESS;
}
