#include <unistd.h>
#include <cstring>
#include "../include/constant.hpp"
#include "../include/common.hpp"
#include "../include/ini_reader.hpp"
#include "../include/server.hpp"

#define ERR_CNF_NOTSET (const char*)("global cnf file not set, program eixt")
#define CNF_DEFFILE (const char*)("./etc/sso.cnf")
char *cnf_filepath = NULL;
IniReader iniReader = NULL;
server_info sinfo;

void setDefCnf();
void opt_handle(int, char **);
void init();

void setDefCnf() {
  if (cnf_filepath == NULL) {
  #ifdef CNF_DEFFILE
    cnf_filepath = (char *)CNF_DEFFILE;
  #endif
  }
}

void opt_handle(int argc, char **argv) {
  int ch;
  int opt_len;
  while ((ch = getopt(argc, argv, "c:")) != -1) {
    switch (ch) {
      case 'c':
        opt_len = strlen(optarg);
        cnf_filepath = (char*) calloc(opt_len+1, sizeof(char));
        memcpy(cnf_filepath, optarg, opt_len);
        break;
      default:

        break;
    }
  }
  setDefCnf();

  if (cnf_filepath == NULL) {
    cout << ERR_CNF_NOTSET << endl;
    exit(-1);
  }
}

void init() {
  IniReader _iniReader((const char*)cnf_filepath);
  iniReader = _iniReader;
  sinfo.host = iniReader.getValue("server", "bind_ip");
  sinfo.port = iniReader.getIntValue("server", "port");
}

void run() {
  Server server(&sinfo);
  server.start();
}

int main(int argc, char **argv) {
  opt_handle(argc, argv);
  cout << "Application Start..." << endl;
  init();
  run();

  return 1;
}
