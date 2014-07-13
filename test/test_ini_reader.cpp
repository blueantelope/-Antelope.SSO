#include "../include/ini_reader.hpp"

void test() {
  IniReader iniReader("test.cnf");
  char *value = iniReader.getValue("test", "username");	
  cout << value << endl;
  value = iniReader.getValue("test", "password");	
  cout << value << endl;
}

int main(int argc, char **argv) {
  test();
  return 1;
}
