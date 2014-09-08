#include "../include/server.hpp"

void test();

void test() {
  host_info sinfo;
  sinfo.host = (char *) string("127.0.0.1").c_str();
  sinfo.port = 10926;
  Server *server = new Server(&sinfo);
  server->start();
}

int main(int argc, char **argv) {
  test();
  return 1;
}
