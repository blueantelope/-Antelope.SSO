#include <unistd.h>
#include "../include/server.hpp"

Server :: Server(server_info *info) {
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
  Server::my_shutdown();
}

void Server :: start() {
  if ((socket_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
    err_sys("socket failed");
    throw "socket failed";
  }

  if (my_bind() < 0) {
    err_sys("bind failed");
    throw "bind failed";
  }

  if (my_listen() < 0) {
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
    int accept_fd = my_accept();
    if (accept_fd != -1) {
      if (clients > MAX_CLIENTS) {
        cout << "ERROR: not accept, max client limit" << endl;
        Server::my_close(accept_fd);
        continue;
      }
      pc = pthread_create(&client_thread[clients], NULL, Server::my_receive, &accept_fd);
      if (pc)
        cout << "ERROR, thread id of client is " << pc << endl;
      else
        clients++;
    }
  }
}

int Server :: my_bind() {
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr(sinfo->host);
  server_addr.sin_port = htons(sinfo->port);

  return bind(socket_fd, (sockaddr *) &server_addr, sizeof(server_addr));
}

int Server :: my_listen() {
  char *ptr;
  int backlog = BACKLOG;
  if ((ptr = getenv("LISTENQ")) != NULL)
      backlog = atoi(ptr);

  return listen(socket_fd, backlog);
}

int Server :: my_accept() {
  sockaddr_in client_addr;
  socklen_t sin_size = sizeof(struct sockaddr_in);
  int accept_fd = accept(socket_fd, (struct sockaddr*) &client_addr, &sin_size);
  if (accept_fd == -1) {
    throw "accept failed";
    return -1;
  }

  cout << "connection from " << (char*) inet_ntoa(client_addr.sin_addr) << endl;
  return accept_fd;
}

void* Server :: my_receive(void *afd_p) {
  int accept_fd = atoi((char *)afd_p);
  cout << "receive from " << accept_fd << endl;
  char buffer[BUFFER_SIZE];
  memset(buffer, 0, BUFFER_SIZE);
  while ((read(accept_fd, buffer, BUFFER_SIZE)) != -1) {
    cout << "recieve message: " << buffer;
  }

  return ((void *) 0);
}

void Server :: write(int accept_fd) {

}

void Server :: my_close(int accept_fd) {
  close(accept_fd);
}

void Server :: my_shutdown() {
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
    Server::my_close(accept_fd);
    accept_fd_set[index] = -1;
  }
  pthread_mutex_unlock(&accept_fd_lock);
}

void Server :: clear_accept_fd_set() {
  pthread_mutex_lock(&accept_fd_lock);
  int n = 0;
  while (n < MAX_CLIENTS) {
    if (accept_fd_set[n] != -1)
      Server::my_close(accept_fd_set[n]);
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
