#ifndef _UTIL_H_
#define _UTIL_H_
#include <iostream>
#include <math.h>
#include<vector>


namespace MD {

  struct vec3 {

    double x;
    double y;
    double z;

    vec3 cross(const vec3 & v) const {
      vec3 newVec;
      vec3 u = *this;
      newVec.x = u.y*v.z - u.z*v.y;
      newVec.y = u.z*v.x - u.x*v.z;
      newVec.z = u.x*v.y - u.y*v.x;
      return newVec;
    }

    double mag() {
      return sqrt(x*x + y*y + z*z);
    }

    void normalize() {

      double mag = sqrt(x*x + y*y + z*z);

      if ( -1e-6 < mag && mag < 1e-6) {
        return;
      }

      x /= mag;
      y /= mag;
      z /= mag;
    }

    // dot product
    inline vec3 operator-(const vec3 & other) const
    {
      vec3 newVec;

      newVec.x = this->x - other.x;
      newVec.y = this->y - other.y;
      newVec.z = this->z - other.z;

      // actual increment takes place here
      return newVec;
    }

    inline vec3 operator-() const
    {
      vec3 newVec;

      newVec.x = -this->x;
      newVec.y = -this->y;
      newVec.z = -this->z;

      // actual increment takes place here
      return newVec;
    }

    // dot product
    inline vec3 operator+(const vec3 & other) const
    {
      vec3 newVec;

      newVec.x = this->x + other.x;
      newVec.y = this->y + other.y;
      newVec.z = this->z + other.z;

      // actual increment takes place here
      return newVec;
    }

    // subtraction product
    inline double operator*(const vec3 & other) const
    {
      double dot = 0;

      dot += this->x * other.x;
      dot += this->y * other.y;
      dot += this->z * other.z;

      // actual increment takes place here
      return dot;
    }

    // subtraction product
    inline vec3 operator*(double other) const
    {
      vec3 newVec = *this;
      newVec.x *= other;
      newVec.y *= other;
      newVec.z *= other;
      return newVec;
    }
  };

  struct color {
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    void brighten(double brightness);

  };

  struct ray3 {
    vec3 origin;
    vec3 direction;
  };

  struct shape {
    virtual bool intersect(const ray3 &, double&, vec3 &, vec3 &) const = 0;
    struct color color;
    shape() {
      color = {0, 0, 0};
    }
    shape(struct color c) {
     color =c;
    }
    const struct color & get_color() const {
      return color;
    }
  };

  struct sphere: shape {
    struct vec3 center;
    double radius;

    bool intersect(const ray3 & ray, double & distance, vec3 & normal, vec3 & intersection_point) const;

    sphere(vec3 cen, double r, struct color c) : shape(c), center(cen), radius(r) {}
  };


  std::ostream& operator<<(std::ostream& os, const MD::vec3& dt);

};
#endif
