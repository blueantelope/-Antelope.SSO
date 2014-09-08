#include <unistd.h>
#include "../include/common.hpp"
#include "../include/server.hpp"

Server :: Server(host_info *info) {
  sinfo = info;
  socket_fd = -1;
  pthread_mutex_init(&accept_fd_lock, NULL);
  memset(accept_fd_set, -1, sizeof(int) * MAX_CLIENTS);
}

Server :: ~Server() {
  Server::halt();
}

void Server :: stop() {
  Server::halt();
}

void Server :: halt() {
  cout << "server halt" << endl;
  Server::clear_accept_fd_set();
  Server::sso_shutdown();
}

void Server :: start() {
  if ((socket_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
    err_sys("socket failed");
    throw "socket failed";
  }

  if (sso_bind() < 0) {
    err_sys("bind failed");
    throw "bind failed";
  }

  if (sso_listen() < 0) {
    err_sys("listen failed");
    throw "listen failed";
  }

  run();
}

void Server :: run() {
  cout << "Server run" << endl;
  int clients = 0;
  int pc;
  while (1) {
    int accept_fd = sso_accept();
    if (accept_fd != -1) {
      if (clients > MAX_CLIENTS) {
        cout << "ERROR: not accept, max client limit" << endl;
        Server::sso_close(accept_fd);
        continue;
      }
      pc = pthread_create(&client_thread[clients], NULL, Server::sso_receive, &accept_fd);
      if (pc)
        cout << "ERROR, thread id of client is " << pc << endl;
      else
        clients++;
    }
  }
}

int Server :: sso_bind() {
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr(sinfo->host);
  server_addr.sin_port = htons(sinfo->port);

  return bind(socket_fd, (sockaddr *) &server_addr, sizeof(server_addr));
}

int Server :: sso_listen() {
  char *ptr;
  int backlog = BACKLOG;
  if ((ptr = getenv("LISTENQ")) != NULL)
      backlog = atoi(ptr);

  return listen(socket_fd, backlog);
}

int Server :: sso_accept() {
  sockaddr_in client_addr;
  socklen_t sin_size = sizeof(struct sockaddr_in);
  int accept_fd = accept(socket_fd, (struct sockaddr*) &client_addr, &sin_size);
  if (accept_fd == -1) {
    throw "accept failed";
    return -1;
  }

  cout << "connection from " << (char*) inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port) << endl;
  return accept_fd;
}

void* Server :: sso_receive(void *afd_p) {
  int accept_fd = *(int *)afd_p;
  cout << "receive from " << accept_fd << endl;
  int rd = 0;
  char buffer[BUFFER_SIZE];
  memset(buffer, 0, BUFFER_SIZE);
  while ((rd = read(accept_fd, buffer, BUFFER_SIZE)) != -1) {
    if (rd == 0) {
      cout << "connect closed by peer" << endl;
      break;
    }
    cout << "recieve message: " << buffer << endl;
    memset(buffer, 0, BUFFER_SIZE);
    Server::sso_write(accept_fd, (char *) "logon from sso server");
  }

  return ((void *) 0);
}

void Server :: sso_write(int accept_fd, char *msg) {
  int len = strlen(msg);
  int pos = 0;
  while (len > 0) {
    cout << "send len:" << len << endl;
    if ((pos = write(accept_fd, msg, len)) <= 0) {
      cout << "send pos:" << pos << endl;
      if (pos < 0 && errno == EINTR)
        pos = 0;
      else
        break;
    }

    len -= pos;
    msg += pos;
  }
}

void Server :: sso_close(int accept_fd) {
  close(accept_fd);
}

void Server :: sso_shutdown() {
  if (socket_fd != -1)
    shutdown(socket_fd, SHUT_RDWR);
}

void Server :: add_accept_fd(int accept_fd) {
  pthread_mutex_lock(&accept_fd_lock);
  int index = get_accept_fd(-1);
  if (index != -1)
    accept_fd_set[index] = accept_fd;
  pthread_mutex_unlock(&accept_fd_lock);
}

void Server :: delete_accept_fd(int accept_fd) {
  pthread_mutex_lock(&accept_fd_lock);
  int index = get_accept_fd(accept_fd);
  if (index != -1) {
    Server::sso_close(accept_fd);
    accept_fd_set[index] = -1;
  }
  pthread_mutex_unlock(&accept_fd_lock);
}

void Server :: clear_accept_fd_set() {
  pthread_mutex_lock(&accept_fd_lock);
  int n = 0;
  while (n < MAX_CLIENTS) {
    if (accept_fd_set[n] != -1)
      Server::sso_close(accept_fd_set[n]);
    n++;
  }

  pthread_mutex_unlock(&accept_fd_lock);
}

int Server :: get_accept_fd(int accept_fd) {
  int n = 0;
  while (n < MAX_CLIENTS) {
    if (accept_fd_set[n] == accept_fd)
      return n;
    n++;
  }

  return -1;
}

