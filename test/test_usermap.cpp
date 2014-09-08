#include "../include/usermap.hpp"

void test() {
  UserMap usermap("../etc/hostgroup", "../etc/usermap");
}

int main(int argc, char **argv) {
  test();
  return 0;
}
