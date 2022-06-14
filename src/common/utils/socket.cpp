#include "common/utils/socket.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <fcntl.h>
#include "common/utils/macro.h"

namespace common {
namespace utils {

uint32_t Socket::IPStringToUInt32(const std::string &ip_str) {
  return inet_addr(ip_str.c_str());
}

std::string Socket::IPUInt32ToString(uint32_t ip) {
  struct sockaddr_in addr;
  addr.sin_addr.s_addr = ip;
  return std::string(inet_ntoa(addr.sin_addr));
}

void Socket::SetNBlock(int socket) {
  int flag = ::fcntl(socket, F_GETFL, 0);
  ::fcntl(socket, F_SETFL, flag | O_NONBLOCK);
}

void Socket::IPv6StringToBuff(const std::string &ip_str, uint8_t buff[16]) {
  inet_pton(AF_INET6, ip_str.c_str(), buff);
}

std::string Socket::IPv6BuffToString(uint8_t buff[16]) {
  char str[1024 + 1];
  BZERO_ARRAY(str);
  inet_ntop(AF_INET6, buff, str, sizeof(str));
  return str;
}

void Socket::SetRecvBufferSize(int socket, int size) {
  ::setsockopt(socket, SOL_SOCKET, SO_RCVBUF, (char *)&size, sizeof(int));
}

void Socket::SetWriteBufferSize(int socket, int size) {
  ::setsockopt(socket, SOL_SOCKET, SO_SNDBUF, (char *)&size, sizeof(int));
}

void Socket::SetKeepAlive(int socket) {
  int one = 1;
  ::setsockopt(socket, SOL_SOCKET, SO_KEEPALIVE, (char *)&one, sizeof(int));
}

void Socket::SetNoDelay(int socket) {
  int one = 1;
  ::setsockopt(socket, IPPROTO_TCP, TCP_NODELAY, (char *)&one, sizeof(int));
}

void Socket::SetReuseAddr(int socket) {
  int one = 1;
  ::setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (char *)&one, sizeof(int));
}

} // namespace utils
} // namespace common
