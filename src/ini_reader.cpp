#include <fstream>
#include "../include/common.hpp"
#include "../include/ini_reader.hpp"

IniReader :: IniReader(const char *filename) {
  ifstream fin(filename);
  fin.clear();
  fin.seekg(0);
  info = new ini_info;
  string line;
  int first = 1;
  int first_node = 0;
  int equ_index = -1;
  int len;
  char start;
  char end;
  int info_len = 0;
  int node_len = 0;
  hash_node *cur_hash = NULL;
  ini_group *cur_group = NULL;
  while (getline(fin, line)) {
    line = trim(line);
    len = line.size();
    if (len < 1)
      continue;
    start = line.at(0);
    switch (start) {
      case '[':
        end = line.at(len-1);
        if (end == ']') {
          ini_group *new_group = new ini_group;
          char *group_name;
          string name = line.substr(1, len-2);
          copy_string(name, &group_name);
          new_group->name = group_name;
          if (!first) {
            cur_group->node->size = node_len;
            cur_group->next = new_group;
            node_len = 0;
          } else {
            first = 0;
            info->group = new_group;
          }
          cur_group = new_group;

          info_len++;
          first_node = 1;
        }
        break;
      case '#':
        break;
      default:
        equ_index = line.find('=', 0);
        if (equ_index != -1) {
          char *key;
          string s_key = line.substr(0, equ_index);
          copy_string(s_key, &key);
          char *value;
          string s_value = line.substr(equ_index+1, len);
          copy_string(s_value, &value);
          hash_node *new_hash = new hash_node;
          char_trim(key);
          new_hash->key = key;
          char_trim(value);
          new_hash->value = value;
          if (!first_node) {
            cur_hash->next = new_hash;
          } else {
            ini_node *new_node = new ini_node;
            new_node->hash = new_hash;
            cur_group->node = new_node;
            first_node = 0;
          }
          cur_hash = new_hash;

          node_len++;
        }
        break;
    }
  }
  if (cur_group != NULL)
    cur_group->node->size = node_len;
  info->size = info_len;

  fin.close();
}

char* IniReader :: getValue(const char *name, const char *key) {
  int n = 0;
  ini_group *cur_group = info->group;
  hash_node *cur_hash = cur_group->node->hash;
  while (n < info->size) {
    if (n > 0)
      cur_group = cur_group->next;
    if (strcmp(name, cur_group->name) == 0) {
      int m = 0;
      while (m < cur_group->node->size) {
        if (m > 0)
          cur_hash = cur_hash->next;
        if (strcmp(key, cur_hash->key) == 0) 
          return cur_hash->value;
        m++;
      }
      break;
    }
    n++;
  }

  return NULL;
}
