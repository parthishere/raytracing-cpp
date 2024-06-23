#include <iostream>
#include <cstdlib>
#include <random>
#include <chrono>
#include <fstream>

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
    for (int j=0; j<image_width; j++){
      double r = rgb(mt);
      double g = rgb(mt);
      double b = rgb(mt);

      if(outputFile.is_open()){
        std::cout << r << " " << g << " " << b << std::endl;
        outputFile << r << " " << g << " " << b << std::endl;
      }
    }
  }
  outputFile.close();
  // std::cout << "Hellow world! " << std::endl;
  
 return EXIT_SUCCESS; 
}
