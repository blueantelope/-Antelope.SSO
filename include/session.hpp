#include "constant.hpp"

#define MAX_GROUP 100
#define MAX_SESSION 1000
#define MAX_NAME_SIZE 200

typedef struct _session_info {
  server_vendor vendor;
  ulong id;
  ulong client_ip;
  ulong last_time;

  void init() {
    vendor.init();
    id = -1;
    client_ip = -1;
    last_time = -1;
  };

  int alive() {
    if (id != -1) return 1;
    return 0;
  };
} session_info;

typedef struct _server_vendor_list {
  server_vendor vendor;
  server_vendor *next;
  server_vendor *last;

  void init() {
    vendor.init();
    next = NULL;
    last = NULL;
  };

  int alive() {
    return vendor.alive();
  };
} server_vendor_list;

typedef struct _server_vendor_group {
  char *name;
  server_vendor_list *vendor_list;
  int size;

  void init() {
    name = NULL;
    vendor_list = NULL;
    size = 0;
  };

  int alive() {
    if (name != NULL)
      return 1;
    return 0;
  };
} server_vendor_group;

class Session {
  public:
    Session();
    ~Session();
    void add_vendor(char *, server_vendor);
    void delete_vendor(server_vendor);
    void update(session_info);
  private:
    server_vendor_group groups[MAX_GROUP];
    session_info sessions[MAX_SESSION];
    int group_size;
    int findGroupByName(char *);
    void init();
};
