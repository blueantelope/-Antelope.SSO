#include "../include/server.hpp"

Server :: Server(server_info *info) {
  sinfo = info;
}

void Server :: start() {
  if ((socket_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
      throw "socket() failed";

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr(sinfo->host);
  server_addr.sin_port = htons(sinfo->port);

  if (bind(socket_fd, (sockaddr *) &server_addr, sizeof(server_addr)) < 0)
    throw "bind() failed";

  if (listen(socket_fd, 10) < 0)
    throw "listen() failed";

  run();
}

void Server :: run() {
  cout << "Server run" << endl;
  while (1) {
    socklen_t sin_size = sizeof(struct sockaddr_in);
    if ((accept_fd = accept(socket_fd, (struct sockaddr*) &client_addr, &sin_size)) == -1 ) {
      throw "accept() failed";
      continue;
    }

    cout << "connection from " << (char*) inet_ntoa(client_addr.sin_addr) << endl;
  }
}
