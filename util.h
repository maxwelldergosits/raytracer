#ifndef _UTIL_H_
#define _UTIL_H_

#include <math.h>


namespace MD {

  struct vec3 {

    double x;
    double y;
    double z;

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
      vec3 newVec;
      if ( -1e-6 <other && other < 1e-6) {
        newVec.x = 0;
        newVec.y = 0;
        newVec.z = 0;
      } else {
        newVec.x = this->x * other;
        newVec.y = this->y * other;
        newVec.z = this->z * other;
      }
      // actual increment takes place here
      return newVec;
    }

    // addtion
    inline vec3 operator+(const vec3 & other) const
    {
      vec3 newVec;
      newVec.x = this->x + other.x;
      newVec.y = this->y + other.y;
      newVec.z = this->z + other.z;
      // actual increment takes place here
      return newVec;
    }

    inline vec3 operator-() const
    {
      vec3 newVec;
      newVec.x = -this->x;
      newVec.y = -this->y;
      newVec.z = -this->z;
      return newVec;
    }




  };


  struct color {
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    void brighten(float brightness) {

      int nred = (int)(red * brightness);
      if (nred > 255) {
        nred = 255;
      }
      red = nred;

      int nblue = (int)(blue *brightness);
      if (nblue > 255) {
        nblue = 255;
      }
      blue = nblue;
      int ngreen = (int)(green * brightness);
      if (ngreen > 255) {
        ngreen = 255;
      }
      green = ngreen;

    }
  };


  struct sphere {
    struct vec3 center;
    double radius;
    struct color color;
  };

  struct ray3 {
    vec3 origin;
    vec3 direction;
  };

}

std::ostream& operator<<(std::ostream& os, const MD::vec3& dt)
{
    os << dt.x << "," << dt.y << "," << dt.z;
    return os;
}

#endif
