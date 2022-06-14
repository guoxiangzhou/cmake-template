#pragma once

#include <stdint.h>
#include <string>

namespace common {
namespace utils {

struct Socket {
  static uint32_t IPStringToUInt32(const std::string &ip_str);
  static std::string IPUInt32ToString(uint32_t ip);

  static void IPv6StringToBuff(const std::string &ip_str, uint8_t buff[16]);
  static std::string IPv6BuffToString(uint8_t buff[16]);

  static void SetNBlock(int socket);
  static void SetRecvBufferSize(int socket, int size);
  static void SetWriteBufferSize(int socket, int size);
  static void SetKeepAlive(int socket);
  static void SetNoDelay(int socket);
  static void SetReuseAddr(int socket);
};

} // namespace utils
} // namespace common
