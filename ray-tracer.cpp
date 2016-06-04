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

    double d = -.5;

    double u = l + (r-l)*(x + .5) / nx;
    double v = b + (t-b)*(y + .5) / ny;

    ray.origin = context.location;

    ray.direction = (context.basis[2] * d) +
                    (context.basis[0] * u) +
                    (context.basis[1] * v);

    ray.direction.normalize();

  }


  int check_intersections(const ray3 & ray, const sphere & s, double & distance) {
    vec3 d = ray.direction;
    vec3 e = ray.origin;
    vec3 c = s.center;


    //                                        (d·d) ((e−c)·(e−c)−R2)
    double discriminant = pow(d * (e-c), 2) - (d*d)*((e-c)*(e-c) - pow(s.radius,2));

    // it merely grazes
    if (discriminant > -1e-6 && discriminant < 1e-6) {
      return 0;
    }

    // doesn't intersect
    if (discriminant < 0) {
      return 0;
    }

    //intersects
    double solA = (((-d)*(e-c)) - sqrt(discriminant)) / (d*d);
    double solB = (((-d)*(e-c)) + sqrt(discriminant)) / (d*d);

    distance = std::min(-solA, -solB);

    return 1;
  }

  int trace_pixel(const raytracer & context, int x, int y, color & result) {

    ray3 ray;
    make_ray(context, x, y, ray);
    int obj_index = -1;
    double min_distance = std::numeric_limits<double>::max();

    for (int i = 0; i< context.objects.size(); i++) {
      double distance = std::numeric_limits<double>::max();
      if (check_intersections(ray, context.objects[i], distance)) {
        if (distance < min_distance) {
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
      vec3 intersection_point = ray.origin + (ray.direction * -min_distance);
      vec3 normal = (intersection_point - context.objects[obj_index].center);
      normal.normalize();
      vec3 v = ray.origin - intersection_point;
      for (int i = 0; i < context.sources.size(); i++) {
        vec3 light = (context.sources[i].position - intersection_point);

        vec3 h = (light + v) * (1/ (light.mag() + v.mag()));

        light.normalize();
        double intensity = (1.0*std::max(0.0, (light * normal))) + 600*pow(std::max(0.0, normal * h), 80);
        result = context.objects[obj_index].color;
        result.brighten(intensity + .2);
      }
    }

    return 0;
  }

  void render(const raytracer & context) {
    cv::Mat image(context.height, context.width, CV_8UC3);
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

    cv::imwrite("output.tiff", image);

  }


}

  int main(int argc, char ** argv) {
    MD::raytracer tracer;

    tracer.location = {0, 0, 0};

    tracer.basis[0] = {1,0,0};
    tracer.basis[1] = {0,0,1};
    tracer.basis[2] = {0,1,0};

    tracer.height = 1080;
    tracer.width = 1920;

    MD::color red =  {0x1, 0x1, 0xff};
    MD::color blue = {0xff, 0x1, 0x1};

    MD::vec3 origin =  {-4,10,0};
    MD::vec3 origin2 = {4,16,0};

    MD::sphere s1 = {origin,  1, red};
    MD::sphere s2 = {origin2, 1, blue};

    MD::vec3 l1_loc = {4, 0, 7};
    MD::color white = {255, 255, 255};

    MD::lightsource l1 = {l1_loc, white};

    tracer.objects.push_back(s1);
    tracer.objects.push_back(s2);

    tracer.sources.push_back(l1);
    MD::render(tracer);
  }
