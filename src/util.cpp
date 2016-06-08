#include "util.h"
namespace MD {

  void color::brighten(double brightness) {

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
  std::ostream& operator<<(std::ostream& os, const MD::vec3& dt)
  {
    os << dt.x << "," << dt.y << "," << dt.z;
    return os;
  }
};
