#include "rtweekend.h"
#include "material.h"
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
    ray scattered;
    color attenuation;
    if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
      return attenuation * ray_color(scattered, world, depth-1);
    return color(0, 0, 0);
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
  auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
  auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
  auto material_left   = make_shared<dielectric>(1.5);
  auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);
  
  world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
  world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.0),   0.5, material_center));
  world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
  world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),  -0.4, material_left));
  world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));

  // Camera
  point3 lookfrom(3,3,2);
  point3 lookat(0,0,-1);
  vec3 vup(0,1,0);
  auto dist_to_focus = (lookfrom-lookat).length();
  auto aperture = 2.0;

  camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);
  
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
