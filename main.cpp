#include "rtweekend.h"
// testing git credentials
#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"

#include <iostream>
using namespace std;

// defines color for all ray/object interactions
color ray_color(const ray &r, const hittable& world, int depth) {
  hit_record rec;
  
  // return no color if recursive depth (number of ray bounces) exceeds threshold
  if (depth <= 0) { return color(0, 0, 0); }
  
  // recursively call ray_color with random reflections
  if (world.hit(r, 0.001, infinity, rec)) {
    vec3 target = rec.point + rec.normal + random_in_unit_sphere();
    return 0.5 * ray_color(ray(rec.point, target - rec.point), world, depth - 1);
  }
  // otherwise shade background with linear gradient
  vec3 unit_direction = unit_vector(r.direction());
  auto y_scal = 0.5*(unit_direction.y() + 1);
  // the returned color is a blend of pure white at t = 0, to pure color at t = 1
  return (1.0-y_scal)*color(1.0, 1.0, 1.0) + y_scal*color(0.5, 0.7, 1.0);
}


int main() {

  // Image

  const auto aspect_ratio = (16.0 / 9.0);
  const int image_width = 400;
  const int image_height = static_cast<int>(image_width / aspect_ratio);
  const int samples_per_pixel = 100;
  const int max_depth = 10;

  // World
  hittable_list world;
  world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
  world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

  // Camera
  camera cam;
  
  // Render

  color grad_color(0.5, 1.0, 0.5);
  cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (int j = image_height-1; j >= 0; j--) {
    cerr << "\rScanlines remaining: " << j << ' ' << flush;
    for (int i = 0; i < image_width; i++) {
      color pixel_color(0, 0, 0);
      for (int s = 0; s < samples_per_pixel; s++) {
	auto u = (double(i)+random_double()) / (image_width - 1);
	auto v = (double(j)+random_double()) / (image_height - 1);
	ray r = cam.get_ray(u, v);
	pixel_color += ray_color(r, world, max_depth);
      }
      write_color(cout, pixel_color, samples_per_pixel);
    }
  }
  cerr << "\nDonezooooo. \n";
}
