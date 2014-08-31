#include "constant.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

typedef struct _server_info {
  char *host;
  int port;
} server_info;

#define BUFFER_SIZE 1024
#define BACKLOG 5
#define MAX_CLIENTS 100

class Server {
  public:
    Server(server_info *);
    ~Server();
    void start();
    void stop();
  private:
    server_info *sinfo;
    int socket_fd;
    sockaddr_in server_addr;
    pthread_t client_thread[MAX_CLIENTS];
    int accept_fd_set[MAX_CLIENTS];
    pthread_mutex_t accept_fd_lock;

    void halt();
    void run();
    int my_bind();
    int my_listen();
    int my_accept();
    static void *my_receive(void *);
    void write(int);
    void my_close(int);
    void my_shutdown();
    void add_accept_fd(int);
    void delete_accept_fd(int);
    void clear_accept_fd_set();
    int get_accept_fd(int);
};
