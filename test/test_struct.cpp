#include <stdio.h>

typedef struct _s1 {
  char *name;
  int n;
  struct _s1 *next;
} s1;

typedef struct _ts {
  s1 *s;
  int size;
} ts;

void test() {
  ts *t = new ts;
  int n = 0;
  s1 *cur;
  while (n < 10) {
    s1 *s = new s1;
    char *name = "test";
    s->name = name;
    s->n = n;
    if (n == 0) {
      t->s = s;
    } else {
      cur->next = s;
    }
    cur = s;
    n++;
  }

  printf("test\n");
}

int main(int argc, char** argv) {
  test();
  return 1;
}
