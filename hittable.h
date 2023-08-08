#ifndef HITTABLE_H
#define HITTABLE_H

#include "rtweekend.h"

class material;

// struct for storing information for instances of ray intersections with objects
struct hit_record {

  point3 point;  // point of hit/intersection
  vec3 normal;  // surface normal at hit point
  double t;  // t parameter of ray at hit point
  bool front_face; // true if ray hits object from outside
  shared_ptr<material> mat_ptr;

  // set normal so that it always points opposite ray
  inline void set_face_normal(const ray& r, const vec3& outward_normal) {
    front_face = dot(r.direction(), outward_normal) < 0;
    // if ray hits from outside, normal dir outward, otw normal dir inward
    normal = front_face ? outward_normal : -outward_normal;
  }
};


// abstract class for hittable objects
class hittable {
  public:
  // hit function takes in a ray, t range, and ref to a hit_record
  // will return true for a positive hit, and update hit_record information, returns false otw
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif

  
