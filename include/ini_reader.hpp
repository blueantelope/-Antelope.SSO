#include <common.hpp>

typedef struct _ini_info {
  char *key;
  char *value;
} ini_info;


class IniReader {
  public:
    IniReader(const char *filename);
    char *getValue(const char *key);
  private:
    ini_info *info;

};
