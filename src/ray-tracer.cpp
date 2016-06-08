#include <limits>
#include<algorithm>
#include <iostream>
#include "ray-tracer.h"
#include <opencv2/opencv.hpp>

namespace MD {

  void make_ray(const raytracer & context, int x, int y, ray3 & ray) {

    double nx = context.width;
    double ny = context.height;

    double l =  -nx / (2 * nx);
    double r =   nx / (2 * nx);
    double b =  -ny / (2 * nx);
    double t =   ny / (2 * nx);

    double d = .5;

    double u = l + (r-l)*(x + .5) / nx;
    double v = b + (t-b)*(y + .5) / ny;

    ray.origin = context.location;

    ray.direction = (context.basis[2] * d) +
      (context.basis[0] * u) +
      (context.basis[1] * v);

    ray.direction.normalize();

  }



  int trace_pixel(const raytracer & context, int x, int y, color & result) {

    ray3 ray;
    make_ray(context, x, y, ray);
    int obj_index = -1;
    double min_distance = std::numeric_limits<double>::max();
    vec3 normal;
    vec3 intersection_point;

    for (int i = 0; i< context.objects.size(); i++) {
      double distance = std::numeric_limits<double>::max();
      vec3 tmp_normal;
      vec3 tmp_intersection_point;
      if (context.objects[i]->intersect(ray,  distance, tmp_normal, tmp_intersection_point)) {
        if (distance < min_distance) {
          normal = tmp_normal;
          intersection_point = tmp_intersection_point;
          min_distance = distance;
          obj_index = i;
        }
      }
    }

    if(obj_index == -1) {

      result.red = 128;
      result.green = 128;
      result.blue = 128;

    } else {
      vec3 v = ray.origin - intersection_point;
      double intensity = 0.0;
      for (int i = 0; i < context.sources.size(); i++) {
        vec3 light = (context.sources[i].position - intersection_point);

        vec3 h = (light + v) * (1/ (light.mag() + v.mag()));

        light.normalize();
        h.normalize();
        normal.normalize();
        double blinn_phong = .2*pow(normal * h, 2);
        if (blinn_phong < 0.0) blinn_phong = 0.0;

        intensity += (.5*std::max(0.0, (light * normal))) + blinn_phong;
      }
      result = context.objects[obj_index]->get_color();
      result.brighten(intensity + .2);
    }

    return 0;
  }

  void render(const raytracer & context) {
    cv::Mat image(context.height, context.width, CV_8UC3);
    cv::Mat imageDownsize(context.height/2, context.width/2, CV_8UC3);
    for (int x = 0; x < context.width; x++) {
      for (int y = 0; y < context.height; y++) {
        color c;

        cv::Vec3b color = image.at<cv::Vec3b>(cv::Point(x,y));

        color.val[0] = c.red;
        color.val[1] = c.green;
        color.val[2] = c.blue;

        trace_pixel(context, x, y, c);
        image.at<cv::Vec3b>(cv::Point(x,y)) = color;

      }
    }
    cv::resize(image, imageDownsize, imageDownsize.size(), cv::INTER_CUBIC);
    cv::imwrite("output.tiff", imageDownsize);

  }


}

int main(int argc, char ** argv) {
  MD::raytracer tracer;

  tracer.location = {0, -2, 0};

  tracer.basis[0] = {1,0,0};
  tracer.basis[1] = {0,0,1};
  tracer.basis[2] = {0,1,0};

  tracer.height = 500*2;
  tracer.width = 500*2;

  MD::color red =  {0x10, 0x10, 0xff};
  MD::color blue = {0xff, 0x10, 0x10};

  MD::vec3 origin =  {-2,5,0};
  MD::vec3 origin2 = {4,8,0};

  MD::vec3 frame000 = {0, 0, 0};
  MD::vec3 frame001 = {0, 0, 1};
  MD::vec3 frame010 = {0, 1, 0};
  MD::vec3 frame100 = {1, 0, 0};

  MD::sphere s1 = {origin,  1, red};
  MD::sphere s2 = {origin2, 1, blue};

  MD::sphere o =  {frame000,  .1, red};
  MD::sphere ax = {frame001,  .1, red};
  MD::sphere ay = {frame010,  .1, red};
  MD::sphere az = {frame100,  .1, red};


  MD::triangle t1{ red,
    {0,  0, -.5 },
    {0,  1, -.5},
    {-1,  0, -.5}
  };

  MD::triangle t2{ red,
    {0,  0, -1 },
    {2,  0, -.5},
    {2,  2, -.5}
  };


  MD::vec3 l1_loc = {-4, 0, 7};
  MD::color white = {255, 255, 255};

  MD::lightsource l1 = {l1_loc, white};

  tracer.objects.push_back(&s1);
  tracer.objects.push_back(&s2);
  tracer.objects.push_back(&t1);
  tracer.objects.push_back(&t2);

  /*
     tracer.objects.push_back(&o);
     tracer.objects.push_back(&ax);
     tracer.objects.push_back(&ay);
     tracer.objects.push_back(&az);
   */

  tracer.sources.push_back(l1);
  MD::render(tracer);
}
