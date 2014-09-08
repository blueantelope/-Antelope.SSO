#include <unistd.h>
#include <cstring>
#include <signal.h>
#include "../include/constant.hpp"
#include "../include/common.hpp"
#include "../include/ini_reader.hpp"
#include "../include/server.hpp"

#define ERR_CNF_NOTSET (const char*)("global cnf file not set, program eixt")
#define CNF_DEFFILE (const char*)("./etc/sso.cnf")
#define ERR_HOSTGROUPS_NOTSET (const char*)("hostgroup file not set, program eixt")
#define HOSTGROUPS_DEFFILE (const char*)("./etc/hostgroup")
#define ERR_USERMAP_NOTSET (const char*)("usermap file not set, program eixt")
#define USERMAP_DEFFILE (const char*)("./etc/usermap")

char *cnf_filepath = NULL;
char *hostgroups_filepath = NULL;
char *usermap_filepath = NULL;
IniReader iniReader = NULL;
server_info sinfo;
Server *server = NULL;

void setDefEtc();
void setDefCnf();
void setDefHostgroups();
void setDefUsermap();
void opt_handle(int, char **);
void init();
void exception_handle();
void sys_exit(int signo);

void setDefEtc() {
  setDefCnf();
  setDefHostgroups();
  setDefUsermap();
}

void setDefCnf() {
  if (cnf_filepath == NULL) {
  #ifdef CNF_DEFFILE
    cnf_filepath = (char *)CNF_DEFFILE;
  #endif
  }

  if (cnf_filepath == NULL) {
    cout << ERR_CNF_NOTSET << endl;
    exit(-1);
  }
}

void setDefHostgroups() {
  if (hostgroups_filepath == NULL) {
  #ifdef HOSTGROUPS_DEFFILE
    hostgroups_filepath = (char *)HOSTGROUPS_DEFFILE;
  #endif
  }

  if (hostgroups_filepath == NULL) {
    cout << ERR_HOSTGROUPS_NOTSET << endl;
    exit(-1);
  }
}

void setDefUsermap() {
  if (usermap_filepath == NULL) {
  #ifdef USERMAP_DEFFILE
    usermap_filepath = (char *)USERMAP_DEFFILE;
  #endif
  }

  if (usermap_filepath == NULL) {
    cout << ERR_USERMAP_NOTSET << endl;
    exit(-1);
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
      case 'h':
        opt_len = strlen(optarg);
        hostgroups_filepath = (char*) calloc(opt_len+1, sizeof(char));
        memcpy(hostgroups_filepath, optarg, opt_len);
        break;
     case 'u':
        opt_len = strlen(optarg);
        usermap_filepath = (char*) calloc(opt_len+1, sizeof(char));
        memcpy(usermap_filepath, optarg, opt_len);
        break;
      default:

        break;
    }
  }

  setDefEtc();
}

void init() {
  IniReader _iniReader((const char*)cnf_filepath);
  iniReader = _iniReader;
  sinfo.host = iniReader.getValue("server", "bind_ip");
  sinfo.port = iniReader.getIntValue("server", "port");
}

void exception_handle() {
  signal(SIGHUP, sys_exit);
  signal(SIGINT, sys_exit);
  signal(SIGKILL, sys_exit);
}

void sys_exit(int signo) {
  if (server != NULL)
    server->stop();
  exit(-1);
}

void run() {
  server = new Server(&sinfo);
  server->start();
}

int main(int argc, char **argv) {
  opt_handle(argc, argv);
  cout << "Application Start..." << endl;
  init();
  exception_handle();
  run();

  return 1;
}
