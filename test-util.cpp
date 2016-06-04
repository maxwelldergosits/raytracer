#include "util.h"
#include <assert.h>


void test_plus() {

  MD::vec3 a = {1,1,1};
  MD::vec3 b = {2,3, 4};
  MD::vec3 c = a + b;

  assert(c.x == 3);
  assert(c.y == 4);
  assert(c.z == 5);
}

int main(void) {

 test_plus();
  return 0;
}
