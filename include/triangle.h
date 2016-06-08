#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_
#include "util.h"
namespace MD {

  struct triangle: public shape {
    vec3 v1, v2, v3;
    bool intersect(const ray3&, double&, vec3 &, vec3 &) const;
    bool intersect_point(const vec3&, double) const;
    triangle(struct color c, vec3 _v1, vec3 _v2, vec3 _v3) : shape(c), v1(_v1), v2(_v2), v3(_v3) {}
    };


}
#endif
