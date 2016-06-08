#include <gtest/gtest.h>

#include "ray-tracer.h"
#include "triangle.h"

TEST(TriangleTest, Intersection) {

  MD::vec3 v1 = {0, 0, 0};
  MD::vec3 v2 = {10, 0, 0};
  MD::vec3 v3 = {10, 10, 0};
  MD::triangle t;
  t.v1 =v1;
  t.v2 =v2;
  t.v3 =v3;

  MD::vec3 p = {0.3, 0.3, 0};
  double tmp = 0;

  ASSERT_TRUE(t.intersect_point(p, tmp));

}

TEST(TriangleTest, NoIntersection) {

  MD::vec3 v1 = {0, 0, 0};
  MD::vec3 v2 = {10, 0, 0};
  MD::vec3 v3 = {10, 10, 0};
  MD::triangle t;
  t.v1 =v1;
  t.v2 =v2;
  t.v3 =v3;

  MD::vec3 p = {-0.1, 0.1, 0};
  double tmp = 0;
  ASSERT_FALSE(t.intersect_point(p, tmp));

}
