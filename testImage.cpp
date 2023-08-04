#include "vec3.h"
#include "color.h"

#include <iostream>
using namespace std;

int main() {

  // Image

  const int width = 256;
  const int height = 256;

  // Render

  cout << "P3\n" << width << ' ' << height << "\n255\n";

  for (int j = height-1; j >= 0; j--) {
    cerr << "\rScanlines remaining: " << j << ' ' << flush;
    for (int i = 0; i < width; i++) {
      color pixel_color(double(i) / width, double(j) / height, 0.25);
      write_color(cout, pixel_color);
    }
  }
  cerr << "\nDonezooooo. \n";
}
