#include "constant.hpp"

typedef struct _thread_info {
  uint max;
  uint min;
  uint initialize;
  ulong expire;
  ulong check_period;
} thread_info;

class ThreadPool {
  public:
    ThreadPool(thread_info *);

  private:
    thread_info *tinfo;
};
