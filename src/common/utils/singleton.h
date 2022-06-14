#pragma once

namespace common {
namespace utils {

template <class T> class Singleton {
public:
  static T &Instance() {
    static T object;
    return object;
  }

protected:
  Singleton(){};
  virtual ~Singleton(){};

private:
  Singleton(const Singleton &);
  Singleton &operator=(const Singleton &);
};

template <typename T> class SingletonModule {
public:
  SingletonModule() { m_instance = &m_module; }

  ~SingletonModule() { m_instance = 0; }

public:
  static T &Instance() { return *m_instance; }

  static T *InstancePtr() { return m_instance; }

private:
  static T *m_instance;

private:
  T m_module;
};

template <typename T> T *SingletonModule<T>::m_instance = 0;

} // namespace utils
} // namespace common