#include "../include/constant.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>

typedef struct _server_info {
  char *host;
  int port;
} server_info;

#define BUFFER_SIZE 1024

class Server {
  public:
    Server(server_info *info);
    void start();
  private:
    server_info *sinfo;
    int socket_fd;
    sockaddr_in server_addr;
    void run();

    int connect();
    void recieve(int);
    void write(int);
    void close(int);
};
