#include "../include/server.hpp"

void test();
void test_header();
void init_header(Header *);

void test() {
  test_header();
}

void test_header() {
  Header header;
  init_header(&header);
  char *str = header.toStr();
  printf("%s\n", str);
}

void init_header(Header *header) {
  header->version = 1;
  int n = 0;
  while (n < 14) {
    header->sn[n] = 2;
    n++;
  }
  header->action = 3;
  n = 0;
  while (n < 16) {
    header->password[n] = 4;
    n++;
  }
  char *url = (char *) "www.blueantelope.com";
  header->dlen = strlen(url);
  header->domain = url;
}

int main(int argc, char **argv) {
  test();
  return 0;
}
