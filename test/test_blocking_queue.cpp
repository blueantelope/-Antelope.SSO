#include "../include/blocking_queue.hpp"

void *put(void *);
void *get(void *);
void test();
BlockingQueue q;

void test() {
  int tid;

  pthread_t put_thread;
  memset(&put_thread, 0, sizeof(put_thread));
  tid = pthread_create(&put_thread, NULL, put, NULL);
  if (tid != 0) {
      cout << "put thread failed" << endl;
      exit(-1);
  }

  pthread_t get_thread;
  memset(&get_thread, 0, sizeof(get_thread));
  tid = pthread_create(&get_thread, NULL, get, NULL);
  if (tid != 0) {
      cout << "get thread failed" << endl;
      exit(-1);
  }

  pthread_join(put_thread, NULL);
  pthread_join(get_thread, NULL);
}

void *put(void *) {
  cout << "put thread create" << endl;
  //int n = 0;
  while (true) {
    cout << "put data" << endl;
    char d1[] = "node1";
    object *v1;
    v1 = (object *) malloc(sizeof(object));
    v1->data = d1;
    v1->dlen = strlen(d1) + 1;
    q.put(v1);
    sleep(2);
  }
}

void *get(void *) {
  cout << "get thread create" << endl;
  object *pd;
  while (true) {
    pd = q.take();
    cout << (char *)pd->data << endl;
  }
}

int main(int argc, char **argv) {
  cout << "test for blocking queue" << endl;
  test();
  return 0;
}
