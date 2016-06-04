#ifndef _RAY_TRACER_H_
#define _RAY_TRACER_H_

#include<vector>
#include"util.h"

namespace MD {

  struct lightsource{
    vec3 position;
    color color;
  };

  struct raytracer {
    std::vector<sphere> objects;
    std::vector<lightsource> sources;
    vec3 location;
    vec3 basis[3];
    unsigned int height;
    unsigned int width;
  };

  int trace_pixel(raytracer * context, int width_index, int height_index, color * result);

};

#endif
