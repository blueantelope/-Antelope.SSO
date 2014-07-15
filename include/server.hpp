#include "../include/constant.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>

typedef struct _server_info {
  char *host;
  int port;
} server_info;

class Server {
  public:
    Server(server_info *info);
    void start();
  private:
    server_info *sinfo;
    int socket_fd, accept_fd;
    sockaddr_in server_addr, client_addr;
    void run();
};
