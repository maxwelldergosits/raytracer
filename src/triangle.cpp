#include "triangle.h"
#include <opencv2/opencv.hpp>


namespace MD {

  bool sameside(vec3 p1, vec3 p2, vec3 a, vec3 b) {
    vec3 cp1 = (b- a).cross(p1 - a);
    vec3 cp2 = (b- a).cross(p2 - a);
    return (cp1 * cp2) >= 0;
  }

  bool triangle::intersect(const ray3 & ray, double & out, vec3 & normal, vec3 & intersection_point) const {
    const vec3 & a = v1;
    const vec3 & b = v2;
    const vec3 & c = v3;
    vec3 n = (b-a).cross(c -a);
    double t = (a - ray.origin) * n / (ray.direction * n);

    if (t< 1e-6) {
      return false;
    }

    vec3 x = ray.origin + (ray.direction*t);
 //   std::cout << "ray.origin = " << ray.origin << "ray.direction = " << ray.direction << "\n";
    normal = n;
    out = t;
    intersection_point = x;

    return intersect_point(x,t);



  }


  bool intersect_pointA(const triangle * t, const vec3 & p) {
    const vec3 & a = t->v1;
    const vec3 & b = t->v2;
    const vec3 & c = t->v3;

    double aABC = (b-a).cross(c-a).mag();
    double alpha = (b-p).cross(c-p).mag() / aABC;

    if (!(0 <= alpha && alpha <= 1)) {
      return false;
    }

    double beta = ((c-p).cross(a-p)).mag() / aABC;

    if (!(0 <= beta && beta <= 1)) {
      return false;
    }

    double gamma = 1 - alpha - beta;
    if (!(0 <= gamma && gamma <= 1)) {
      return false;
    }

    return true;
  }


  bool intersect_pointB(const triangle * t, const vec3 & p) {
    vec3 V0 = t->v3 - t->v1;
    vec3 V1 = t->v2 - t->v1;
    vec3 V2 = p - t->v1;
    double dot00 = V0 * V0;
    double dot01 = V0 * V1;
    double dot02 = V0 * V2;
    double dot11 = V1 * V1;
    double dot12 = V1 * V2;
    double invDenom = 1.0 / (dot00 * dot11 - dot01 * dot01);
    double u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    double v = (dot00 * dot12 - dot01 * dot02) * invDenom;
    return (u >= 0) && (v >= 0) && (u+v < 1);
  }

  bool triangle::intersect_point(const vec3 & p, double t) const {
    return intersect_pointB(this, p);
  }

};
