#include <iostream>
#include <cstdlib>
#include <random>
#include <chrono>
#include <fstream>

#include "vec3.h"
#include "color.h"

std::random_device rd{};
std::seed_seq ss {
  static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()),
  rd(), rd(), rd(), rd(), rd(), rd()
};
std::mt19937 mt{ss};

std::uniform_int_distribution rgb {0, 255};

int main(){
  std::ofstream outputFile("output.ppm");

  int image_width = 256;
  int image_height = 256;

  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

  for (int i=0; i<image_height; i++){
    std::clog << "\rScanlines remaining: " << (image_height - i) << ' ' << std::flush;
    for (int j=0; j<image_width; j++){
      auto pixel_color = color(rgb(mt), rgb(mt), rgb(mt));

      if(outputFile.is_open()){
        write_color(std::cout, pixel_color);
        write_color(outputFile, pixel_color);
      }
    }
  }
  outputFile.close();
  // std::cout << "Hellow world! " << std::endl;
  std::clog << "\rDone.                 \n";
 return EXIT_SUCCESS; 
}
