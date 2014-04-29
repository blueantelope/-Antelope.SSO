#include <iostream>
#include <string>
#include <sstream>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <stdlib.h>
#include <cstring>
#include <stdarg.h>

#define buffer_size 1024
#define line_size	258
#define _debug 1

typedef unsigned int uint;

using namespace std;

string ltrim(string);
string rtrime(string);
string trim(string);
int count_line(string);
int count_line(istream&);

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

int count_line(string s) {
	istringstream in; 
	in.str(s);
	return count_line(in);
}

int count_line(istream &in) {
	int n = 0;
	string temp;
	while (getline(in, temp))		n++;
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

void debug_println(char *msg, ...) {
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
/*
void debug_println(string msg, ...) {
	if (1) {
		string message;
		va_list list;
		va_start(list, msg);
		while (1) {
			message = va_arg(list, string);
			if (message == NULL)
				break;
			cout << message;
		}
		cout << endl;
		va_end("list");
	}
}
*/
