#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define _debug        1
#define buffer_size   1024
#define line_size     258

typedef unsigned short ushrot;
typedef unsigned int uint;
typedef unsigned long ulong;

#define pvoid void *

#define err_sys(info) {                               \
  fprintf(stderr, "%s:%s\n", info, strerror(errno));  \
  exit(EXIT_FAILURE);                                 \
}

using namespace std;
