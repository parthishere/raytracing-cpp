#ifndef CAMERA_H
#define CAMERA_H

#include "macros.hpp"

#include "hittable.hpp"



class Camera
{
public:
    int image_width{400};
    double aspect_ratio{16.0 / 9.0};
    

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

        for (int i = 0; i < image_height; i++)
        {
            std::clog << "\rScanlines remaining: " << (image_height - i) << ' ' << std::flush;
            for (int j = 0; j < image_width; j++)
            {
                point3 pixel_center = pixel00_loc + (i * pixel_delta_y) + (j * pixel_delta_x);
                vec3 ray_direction = pixel_center - camera_center;

                Ray ray(camera_center, ray_direction);

                // vec3 pixel_color = vec3(rgb(mt), rgb(mt), rgb(mt)); // random pixels
                vec3 pixel_color = ray_color(ray, world);

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
    }

private:
    int image_height;
    vec3 pixel_delta_x;
    vec3 pixel_delta_y;
    point3 pixel00_loc;
    point3 camera_center;
    std::ofstream outputFile;

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

    color ray_color(const Ray &ray, const Hittable &world) const
    {

        HitRecord record;
        if (world.hit(ray, Interval(0, infinity), record))
        {
            // The vector (Point_along_ray - C) points from the center of the sphere to the surface.
            return 0.5 * (record.normal + color(1, 1, 1));
        }

        vec3 unit_direction = unit_vector(ray.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
    }
};

#endif