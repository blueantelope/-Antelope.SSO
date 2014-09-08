#include "constant.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

#define HOST_SIZE   200

typedef struct _host_info {
  char *host;
  int port;

  void init() {
    host = (char *) malloc(HOST_SIZE * sizeof(char));
  };

  void getClientHost(int client_fd) {
    socklen_t len;
    struct sockaddr_in addr;
    int ret = getpeername(client_fd, (struct sockaddr *) &addr, &len);
    if (ret < 0)  return;
    inet_ntop(AF_INET, &addr.sin_addr, host, HOST_SIZE);
    port = ntohs(addr.sin_port);
  }

  char *tostr() {
    char *str;
    str = (char *) malloc(200 * sizeof(char));
    sprintf(str, "host=%s, port=%d", host, port);

    return str;
  };
} host_info;

typedef struct _packet {
  byte version;
  byte sn[14];
  byte action;
  byte password[16];
  ushort dlen;
  char *domain;

  _packet() {
    printf("packet construct()\n");
    version = 0;
    int n = 0;
    while (n < 14)
      sn[n++] = 0;
    action = 0;
    n = 0;
    while (n < 16)
      password[n++] = 0;
    dlen = 0;
    domain = NULL;
  }

  byte *domain2byte() {
    byte *dbyte;
    dbyte = (byte *) malloc(dlen * sizeof(char));
    int n = 0;
    while (n < dlen) {
      dbyte[n] = (uint) *domain;
      n++;
      domain++;
    }

    return dbyte;
  }

  char *toMessage() {
    int len = 18 +  dlen;
    char *msg;
    msg = (char *) malloc(len * sizeof(char));
    *msg = version;
    msg++;
    int n = 0;
    while (n < 15) {
      *msg = sn[n];
      msg++;
      n++;
    }
    *msg = action;
    n = 0;
    while (n < 16) {
      *msg = password[n];
      msg++;
      n++;
    }
    *msg = (dlen & 0xFF00) >> 8;
    msg++;
    *msg = dlen & 0xFF;
    msg++;
    byte *dbyte = domain2byte();
    n = 0;
    while (n < dlen) {
      *msg = *dbyte;
      msg++;
      dbyte++;
      n++;
    }

    return msg;
  };
} packet;

#define BUFFER_SIZE 1024
#define BACKLOG 5
#define MAX_CLIENTS 100

class Server {
  public:
    Server(host_info *);
    ~Server();
    void start();
    void stop();
  private:
    host_info *sinfo;
    int socket_fd;
    sockaddr_in server_addr;
    pthread_t client_thread[MAX_CLIENTS];
    int accept_fd_set[MAX_CLIENTS];
    pthread_mutex_t accept_fd_lock;

    void halt();
    void run();
    int sso_bind();
    int sso_listen();
    int sso_accept();
    static void *sso_receive(void *);
    static void sso_write(int, char *);
    void sso_close(int);
    void sso_shutdown();
    void add_accept_fd(int);
    void delete_accept_fd(int);
    void clear_accept_fd_set();
    int get_accept_fd(int);
};
