#include <ini_reader.hpp>
#include <iostream>

using namespace std;

void test() {
  IniReader iniReader("test.cnf");
	char *value = iniReader.getValue("test", "username");	
	cout << value << endl;
}

int main(int argc, char **argv) {
  test();
  return 1;
}
