#include <iostream>
#include <string>
#include <sstream>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <stdlib.h>
#include <cstring>

#define buffer_size 1024;
#define line_size	258;

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

char *static_c(const char *c) {
	int len = strlen(c);
	char *new_c;
	new_c = (char *) malloc(len * sizeof(char));
	int n = 0;
	while (n < len) {
		*new_c = *c;	
		new_c++, c++, n++;
	}
	new_c -= n;
	return new_c;
}

