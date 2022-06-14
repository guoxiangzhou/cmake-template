#pragma once

#include <condition_variable>
#include <mutex>

namespace common {
namespace thread {

using Cond = std::condition_variable;
using Mutex = std::mutex;
using MutexLocker = std::unique_lock<std::mutex>;

class NilMutex {
public:
  void lock() {}
  void unlock() {}
};

} // namespace thread
} // namespace common
