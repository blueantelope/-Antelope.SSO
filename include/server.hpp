#include "constant.hpp"
#include "common.hpp"
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

typedef struct _Header {
  byte version;
  byte sn[14];
  byte action;
  byte password[16];
  ushort dlen;
  char *domain;
  int body_len;

  _Header() {
    printf("Header construct()\n");
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

  int length(const char *format) {
    return (strlen(format) + 100) * sizeof(char);
  }

  char *bytearrayTostr(const char *format, byte *param, int len) {
    char *str;
    str = (char *) malloc(length(format));
    char *arg;
    arg = (char *) malloc(len * sizeof(char));
    int n = 0;
    while (n < len) {
      *arg = int2char((int) (*param));
      param++; arg++; n++;
    }
    arg -= len;
    sprintf(str, format, arg);
    return str;
  }

  char *toStr() {
    const char *version_format = "version = %d, ";
    char *version_str;
    version_str = (char *) malloc(length(version_format));
    sprintf(version_str, version_format, (int) version);

    const char *sn_format = "sn = %s, ";
    char *sn_str = bytearrayTostr(sn_format, sn, 14);

    const char *action_format = "action = %d, ";
    char *action_str;
    action_str = (char *) malloc(length(action_format));
    sprintf(action_str, action_format, (int) action);

    const char *password_format = "password = %s, ";
    char *password_str = bytearrayTostr(password_format, password, 16);

    const char *dlen_format = "dlen = %d, ";
    char *dlen_str;
    dlen_str = (char *) malloc(length(dlen_format));
    sprintf(dlen_str, dlen_format, (int) dlen);

    const char *domain_format = "domain = %s";
    char *domain_str;
    domain_str = (char *) malloc(length(domain_format));
    sprintf(domain_str, domain_format, domain);

    char *str;
    str = (char *) malloc(1000 * sizeof(char));
    strcpy(str, version_str);
    strcat(str, sn_str);
    strcat(str, action_str);
    strcat(str, password_str);
    strcat(str, dlen_str);
    strcat(str, domain_str);

    return str;
  };
} Header;

typedef struct _Body {
  byte *data;
  int data_len;
} Body;

typedef struct _Packet {
  Header header;
  Body body;
  
} Packet;

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
    static void printHex(char *,  int, int);
    static char *fetchMsg(char *, int);
};
