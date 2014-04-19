#include <ini_reader.hpp>
#include <fstream>

IniReader :: IniReader(const char *filename) {
  ifstream fin(filename);
  string line;
  while (getline(fin, line)) {
    cout << line << endl;
  }

  fin.close();
}




