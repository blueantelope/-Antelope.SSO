typedef struct _ini_group {
  char *key;
  char *value;
  struct _ini_group *next;
} ini_group;

typedef struct _ini_info {
	char *name;
	ini_group *group;
	struct _ini_info *next;
} ini_info;

class IniReader {
  public:
    IniReader(const char *filename);
    char *getValue(const char *name, const char *key);
  private:
    ini_info *info;
};
