#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define _debug        1
#define buffer_size   1024
#define line_size     258
#define max_line      100

typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned char byte;

#define pvoid void *

#define err_sys(info) {                               \
  fprintf(stderr, "%s:%s\n", info, strerror(errno));  \
  exit(EXIT_FAILURE);                                 \
}

using namespace std;

/*
typedef struct _server_vendor {
  uint id;
  char *name;
  char *password;
  char *host;
  char *domain;

  void init() {
    id = -1;
    name = NULL;
    password = NULL;
    host = NULL;
    domain = NULL;
  };

  int alive() {
    if (id != -1) return 1;
    return 0;
  };
} server_vendor;
*/
