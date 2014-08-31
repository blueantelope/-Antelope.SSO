#include "../include/session.hpp"

Session :: Session() {
  init();
}

Session :: ~Session() {

}

void Session :: init() {
  // init for vendor_group
  int n = 0;
  while (n < MAX_GROUP)
    groups[n++].init();
  // init for session
  n = 0;
  while (n < MAX_SESSION)
    sessions[n++].init();
}

void Session :: add_vendor(char *name, server_vendor vendor) {
  int index = findGroupByName(name);
  if (index != -1) {
    index = group_size++;
    strcpy(name, groups[index].name);
  }
  // add vendor to group
  server_vendor_group group = groups[index];
  server_vendor_list *list = group.vendor_list;
  list += group.size;
  list->next = &vendor;
  server_vendor last = list->vendor;
  list++;
  list->last = &last;
  list->vendor = vendor;
  list->next = NULL;
  group.size++;
}

void Session :: delete_vendor(server_vendor vendor) {

}

void Session :: update(session_info info) {

}

int Session :: findGroupByName(char *name) {
  int n = 0;
  while (n < group_size) {
    if (groups[n].alive() && (strcmp(groups[n].name, name) == 0))
      return n;
    n++;
  }

  return -1;
}
