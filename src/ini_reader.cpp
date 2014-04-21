#include <common.hpp>
#include <ini_reader.hpp>
#include <fstream>
#include <malloc.h>

IniReader :: IniReader(const char *filename) {
	ifstream fin(filename);
	int lines = count_line(fin);
	fin.clear();
	fin.seekg(0);
	int info_len = lines * line_size;
	info = new ini_info[info_len];
	string line;
	int first = 1;
	int equ_index = -1;
	int len;
	char start;
	char end;
  while (getline(fin, line)) {
		cout << line << endl;

		line = trim(line);
		len = line.size();
		if (len < 1)	continue;
		start = line.at(0);
		switch (start) {
			case '[':
				end = line.at(len-1);
				if (end == ']') {
					if (!first)		info->next = ++info;
					else					first = 0;
					string name = line.substr(1, len-2);
					info->name = static_c(name.c_str());
				}
				break;
			case '#':
				break;
			default:
				equ_index = line.find('=', 0);
				if (equ_index != -1) {
					info->group	= new ini_group;
					info->group->key = static_c(line.substr(0, equ_index).c_str());
					info->group->value = static_c(line.substr(equ_index+1, len).c_str());
					cout << "group.key = " << info->group->key << endl;
					cout << "group.value = " << info->group->value << endl;
					info->group++;
				}
				break;
		}
  }


 fin.close();
}

char* IniReader :: getValue(const char *name, const char *key) {
			

}
