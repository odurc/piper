#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "sockme.hpp"

namespace sockme {
  Server::Server(int port) : port(port) {}

  bool Server::start() {
    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
      std::cerr << "Failed to create socket\n";
      return false;
    }

    sockaddr_in address;

    // Set up address structure
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Bind socket to address
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
      return false;
    }

    // Listen for incoming connections
    if (listen(server_fd, 5) < 0) {
      return false;
    }

    return true;
  }

  void Server::accept() {
    sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);

    // Accept incoming connection
    client_fd = ::accept(server_fd, 
      (struct sockaddr *)&client_addr, (socklen_t *)&client_addr_len);

    if (client_fd < 0) {
      return;
    }
  }

  int Server::recv(std::string *msg) {
    char buffer[2048];
    int len = ::recv(client_fd, buffer, sizeof buffer, 0);

    *msg = "";

    // TODO: handle error, i.e. len < 0
    if (len < 0) {
      return len;
    }

    buffer[len] = 0;
    *msg = buffer;

    // just a hack for now
    close(client_fd);
    client_fd = -1;

    return len;
  }

  void Server::stop() {
    close(server_fd);
  }

} // namespace sockme

