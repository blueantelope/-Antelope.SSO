#include "constant.hpp"

typedef struct _hash_node {
  char *key;
  char *value;
  struct _hash_node *next;
} hash_node;

typedef struct _ini_node {
  hash_node *hash;
  int size;
} ini_node;

typedef struct _ini_group {
  char *name;
  ini_node *node;
  struct _ini_group *next;
} ini_group;

typedef struct _ini_info {
  ini_group *group;
  int size;
} ini_info;

class IniReader {
  public:
    IniReader(const char *filename);
    char *getValue(const char *name, const char *key);
    int getIntValue(const char *name, const char *key);
  private:
    ini_info *info;
};
