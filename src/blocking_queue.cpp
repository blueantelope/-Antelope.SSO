#include "../include/blocking_queue.hpp"

BlockingQueue :: BlockingQueue() {
  init();
}

void BlockingQueue :: init() {
  //pthread_rwlock_init(&rwlock, NULL);
  pthread_mutex_init(&lock, NULL);

  size = 0;
  node *head;
  head = (node *) malloc(sizeof(node));
  head->value = NULL;
  head->prev = NULL;
  head->next = NULL;
  qnode = head;
}

object * BlockingQueue :: take() {
  while (true) {
    object *o = dequeue();
    if (o != NULL)
      return dequeue();
  }
}

void BlockingQueue :: put(object *value) {
  enqueue(value);
}

void BlockingQueue :: enqueue(object *value) {
  //pthread_rwlock_wrlock(&rwlock);
  pthread_mutex_lock(&lock);
  node *dnode;
  dnode = (node *) malloc(sizeof(node));
  dnode->value = (object *) malloc(sizeof(object));
  void *data;
  data = (void *) calloc(value->dlen, sizeof(char));
  memcpy(data, value->data, value->dlen);
  dnode->value->data = data;
  dnode->value->dlen = value->dlen;
  dnode->prev = qnode;
  qnode->next = dnode;

  size++;
  qnode = dnode;
  //pthread_rwlock_unlock(&rwlock);
  pthread_mutex_unlock(&lock);
}

object * BlockingQueue :: dequeue() {
  //pthread_rwlock_wrlock(&rwlock);
  pthread_mutex_lock(&lock);
  if (size == 0)
    return NULL;
  object *value = qnode->value;
  object *ret;
  ret = (object *) malloc(sizeof(object));
  void *d;
  d = (void *) calloc(value->dlen, sizeof(char));
  memcpy(d, value->data, value->dlen);
  ret->data = d;
  ret->dlen = value->dlen;
  //pthread_rwlock_unlock(&rwlock);

  //pthread_rwlock_wrlock(&rwlock);
  free(qnode->value->data);
  free(qnode->value);
  qnode = qnode->prev;
  size -= 1;
  //pthread_rwlock_unlock(&rwlock);
  pthread_mutex_unlock(&lock);
  return ret;
}

