
typedef struct _server_info {
  char* host;
  int port;
} server_info;

class Server {
  public:
    Server(server_info* info);
    start();

}

