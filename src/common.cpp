#include <iostream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include <cstring>
#include <stdarg.h>
#include "../include/common.hpp"

string ltrim(string s) {
  s.erase(s.begin(), find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));
  return s;
}

string rtrim(string s) {
  s.erase(find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(), s.end());
  return s;
}

string trim(string s) {
  return ltrim(rtrim(s));
}

void char_ltrim(char *s) {
  char *p;
  p = s;
  while(*p == ' ' || *p == '\t') {
    p++;
  }
  strcpy(s, p);
}

void char_rtrim(char *s) {
  int i;
  i = strlen(s)-1;
  while((s[i] == ' ' || s[i] == '\t') && i >= 0) {
    i--;
  };
  s[i+1] = '\0';
}

void char_trim(char *s) {
  char_ltrim(s);
  char_rtrim(s);
}

int count_line(string s) {
  istringstream in;
  in.str(s);
  return count_line(in);
}

int count_line(istream &in) {
  int n = 0;
  string temp;
  while (getline(in, temp))
    n++;
  return n;
}

void copy_string(string s, char **new_c) {
  const char *c = s.c_str();
  int len = strlen(c);
  *new_c = new char[len];
  int n = 0;
  while (n < len) {
    **new_c = *c;
    (*new_c)++, c++, n++;
  }
  *new_c -= n;
}

void debug_print(char *msg, ...) {
  if (_debug) {
    char *message;
    va_list list;
    va_start(list, msg);
    while (1) {
      message = va_arg(list, char *);
      if (strcmp(message , "/0") == 0)
        break;
      cout << message;
    }
    cout << endl;
    va_end(list);
  }
}

char int2char(int d) {
  char *c;
  c = (char *) malloc(1 * sizeof(char));
  sprintf(c, "%d", d);
  return *c;
}
