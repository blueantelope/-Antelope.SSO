#include "../include/usermap.hpp"
#include <fstream>

UserMap :: UserMap(const char *hostgroup_file, const char *usermap_file) {
  readHostgroup(hostgroup_file);
  readUsermap(usermap_file);
};

UserMap :: ~UserMap() {

};

void UserMap :: readHostgroup(const char *hostgroup_file) {
  ifstream fin(hostgroup_file);
  fin.clear();
  fin.seekg(0);
  string line;
  while (getline(fin, line)) {
    cout << line << endl;
  }
}

void UserMap :: readUsermap(const char *usermap_file) {
  ifstream fin(usermap_file);
  fin.clear();
  fin.seekg(0);
  string line;
  while (getline(fin, line)) {
    cout << line << endl;
  }
}
