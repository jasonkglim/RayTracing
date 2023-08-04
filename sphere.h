#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

// class declarations for sphere object, inheriting from hittable class
class sphere : public hittable {
  public:
    sphere() {}
    sphere(const point3& cen, double r) : center(cen), radius(r) {}

    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

  public:
    point3 center;
    double radius;
};


// class implementations
bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
  // ray-sphere intersection quadratic math
  vec3 oc = r.origin() - center;
  auto a = r.direction().length_squared();
  auto half_b = dot(oc, r.direction());
  auto c = oc.length_squared() - radius*radius;

  auto discriminant = half_b*half_b - a*c;
  if (discriminant < 0) return false;
  auto sqrtd = sqrt(discriminant);

  // find nearest root in accepted t range
  auto root = (-half_b - sqrtd) / a;
  if (root < t_min || root > t_max) {
    root = (-half_b + sqrtd) / a;
    if (root < t_min || root > t_max) {
      return false;
    }
  }
  
  // if not returned false at this point, hit is valid, update record
  rec.t = root;
  rec.point = r.at(rec.t);
  vec3 outward_normal = (rec.point - center) / radius;
  rec.set_face_normal(r, outward_normal);

  return true;
}

#endif
