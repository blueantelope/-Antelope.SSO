#include "constant.hpp"
#include <pthread.h>

typedef struct _object {
  void *data;
  uint dlen;
} object;

typedef struct _node {
  object *value;
  struct _node *prev;
  struct _node *next;
} node;

class BlockingQueue {
  public:
    BlockingQueue();
    object *take();
    void put(object *value);
  private:
    int size;
    node *qnode;
    //pthread_rwlock_t rwlock;
    pthread_mutex_t lock;
    void init();
    void enqueue(object *value);
    object *dequeue();
};
