#include "../include/server.hpp"

void test();
void init(packet *);

void test() {
  packet p;
  init(&p);
  char *msg = p.toMessage();
  printf("%s\n", msg);
}

void init(packet *p) {
  p->version = 1;
  int n = 0;
  while (n < 14) {
    p->sn[n] = 2;
    n++;
  }
  p->action = 3;
  n = 0;
  while (n < 16) {
    p->password[n] = 4;
    n++;
  }
  char *url = (char *) "www.blueantelope.com";
  p->dlen = strlen(url);
  p->domain = url;
}

int main(int argc, char **argv) {
  test();
  return 0;
}
