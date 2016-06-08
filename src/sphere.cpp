#include "util.h"
namespace MD {
  bool sphere::intersect(const ray3 & ray, double & distance, vec3 & normal, vec3 & intersection_point) const {
    vec3 d = ray.direction;
    vec3 e = ray.origin;
    vec3 c = this->center;


    //                                        (d·d) ((e−c)·(e−c)−R2)
    double discriminant = pow(d * (e-c), 2) - (d*d)*((e-c)*(e-c) - pow(this->radius,2));

    // it merely grazes
    if (discriminant > -1e-6 && discriminant < 1e-6) {
      return false;
    }

    // doesn't intersect
    if (discriminant < 0) {
      return false;
    }
    //intersects
    double solA = (((-d)*(e-c)) - sqrt(discriminant)) / (d*d);
    double solB = (((-d)*(e-c)) + sqrt(discriminant)) / (d*d);

    distance = std::min(-solA, -solB);

    intersection_point = ray.origin + (ray.direction * -distance);
    normal = (intersection_point - this->center);

    normal.normalize();

    return true;;
  }
}
