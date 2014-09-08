#include "common.hpp"

typedef struct _user_map {
  char *username;
  server_vendor *vendor;
  int size;
} user_map;

typedef struct _group_user_map {
  char *group;
  user_map *umap;
  int size;
} group_user_map;

class UserMap {
  public:
    UserMap(const char *, const char *);
    ~UserMap();

  private:
    group_user_map gu_map;
    
    void readUsermap(const char *);
    void readHostgroup(const char *);

};
