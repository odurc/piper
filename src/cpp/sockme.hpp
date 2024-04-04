#ifndef SOCKME_H
#define SOCKME_H

#include <string>

namespace sockme {

  class Server {
  private:
    int server_fd;
    int port;
    int client_fd;

  public:
    Server(int port);

    bool start();
    void accept();
    int recv(std::string *msg);
    void stop();
  };

} // namespace sockme

#endif // SOCKME_SERVER_H
