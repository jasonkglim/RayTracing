#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>
using namespace std;


void write_color(ostream& out, color pixel_color, double samples_per_pixel) {
  // pixel_color components represent sum of sample values
  auto r = sqrt(pixel_color.x() / samples_per_pixel);
  auto g = sqrt(pixel_color.y() / samples_per_pixel);
  auto b = sqrt(pixel_color.z() / samples_per_pixel);
  
  // Write the translated [0,255] value of each color component.
  out << static_cast<int>(256 * clamp(r, 0, 0.999)) << ' '
      << static_cast<int>(256 * clamp(g, 0, 0.999)) << ' '
      << static_cast<int>(256 * clamp(b, 0, 0.999)) << '\n'; 
}

#endif

