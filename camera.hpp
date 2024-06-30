#ifndef CAMERA_H
#define CAMERA_H

#include "macros.hpp"

#include "hittable.hpp"
#include "random.hpp"

class Camera
{
public:
    int image_width{400};            // Rendered image width in pixel count
    double aspect_ratio{16.0 / 9.0}; // Ratio of image width over height
    int samples_per_pixel = 10;      // Count of random samples for each pixel
    int max_depth = 10;              // Maximum number of ray bounces into scene

    void render(const Hittable &world)
    {
        initialize();

        // render
        std::cout << "P3\n"
                  << image_width << ' ' << image_height << "\n255\n";
        if (outputFile.is_open())
        {
            outputFile << "P3\n"
                       << image_width << ' ' << image_height << "\n255\n";
        }

        for (int h_px = 0; h_px < image_height; h_px++)
        {
            std::clog << "\rScanlines remaining: " << (image_height - h_px) << ' ' << std::flush;
            for (int w_px = 0; w_px < image_width; w_px++)
            {
                color average_color(0, 0, 0);
                for (int k = 0; k < samples_per_pixel; k++)
                {

                    // vec3 pixel_color = vec3(rgb(mt), rgb(mt), rgb(mt)); // random pixels
                    Ray r = random_ray_at_pixel(w_px, h_px);
                    average_color += ray_Color(r, max_depth, world);
                }

                if (outputFile.is_open())
                {
                    // write_color(std::cout, (average_color/samples_per_pixel));
                    write_color(outputFile, (average_color / samples_per_pixel));
                }
            }
        }
        outputFile.close();
        // std::cout << "Hellow world! " << std::endl;
        std::clog << "\rDone.                 \n";
    }

private:
    int image_height;
    vec3 pixel_delta_x;
    vec3 pixel_delta_y;
    point3 pixel00_loc;
    point3 camera_center;
    std::ofstream outputFile;
    Random random{};

    void initialize()
    {
        outputFile.open("output.ppm", std::ios::out | std::ios::trunc);

        image_height = image_width / aspect_ratio;
        image_height = image_height < 1 ? 1 : image_height;

        double focal_length{1.0};
        camera_center = {0, 0, 0};

        double viewport_height{2.0};
        //  I have not used aspect ratio as when computing viewport_width, it's because the value set to aspect_ratio is the ideal ratio, it may not be the actual ratio between image_width and image_height. If image_height was allowed to be real valued—rather than just an integer—then it would be fine to use aspect_ratio. But the actual ratio between image_width and image_height can vary based on two parts of the code. First, image_height is rounded down to the nearest integer, which can increase the ratio. Second, we don't allow image_height to be less than one, which can also change the actual aspect ratio.
        double viewport_width = viewport_height * (double(image_width) / image_height);

        // Calculate the vectors across the horizontal and down the vertical viewport edges.
        vec3 viewport_x_vec{viewport_width, 0, 0};
        vec3 viewport_y_vec{0, -viewport_height, 0};

        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        pixel_delta_x = viewport_x_vec / image_width;
        pixel_delta_y = viewport_y_vec / image_height;

        // Calculate the location of the upper left pixel.
        point3 viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_x_vec / 2 + ((-1 * viewport_y_vec) / 2);
        pixel00_loc = viewport_upper_left + (0.5 * (pixel_delta_x + pixel_delta_y));
    }

    Ray random_ray_at_pixel(int pixel_width_index, int pixel_height_index)
    {
        auto offset = random.sample_square();
        point3 pixel_center = pixel00_loc + ((pixel_height_index + offset.y()) * pixel_delta_y) + ((pixel_width_index + offset.x()) * pixel_delta_x);
        vec3 ray_direction = pixel_center - camera_center;

        Ray ray(camera_center, ray_direction);
        return ray;
    }

    color ray_Color(const Ray &ray, int max_depth, const Hittable &world) const
    {
        // If we've exceeded the ray bounce limit, no more light is gathered.
        if (max_depth <= 0)
            return color(0, 0, 0);

        HitRecord record;
        if (world.hit(ray, Interval(0.001, infinity), record))
        {
            vec3 direction = random_on_hemisphere(record.normal);
            // The vector (Point_along_ray - C) points from the center of the sphere to the surface.
            return 0.5 * ray_Color(Ray(record.point, direction), max_depth - 1, world);
        }

        vec3 unit_direction = unit_vector(ray.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
    }
};

#endif