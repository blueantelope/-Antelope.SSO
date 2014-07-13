#include "../include/common.hpp"

static void test_trim();
static void test_count_line();

void test() {
  test_count_line();
}

static void test_trim() {
  string s("     name = root     ");
  s = trim(s);
  cout << s << endl;
}

static void test_count_line() {
  string s("sdf\nsdf\nsdfsdf\nsdf\nsdfs\nsdfsdf\ns\ns\ns\n");
  int count = count_line(s);
  cout << count << endl;
}

int main(int argc, char **argv) {
  test();
  test_trim();
  return 1;
}
