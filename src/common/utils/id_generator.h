#pragma once

#include "common/thread/mutex.h"

namespace common {
namespace utils {

template <typename LOCK = thread::NilMutex> class IdGenerator {
public:
  IdGenerator() { m_use_bit_table = NULL; }

  IdGenerator(int32_t min_id, int32_t max_id) {
    Initialize(min_id, max_id, min_id);
  }

  ~IdGenerator() { Destroy(); }

  //! Range : [min_id, max_id)
  //! begin_id : min_id <= begin_id < max_id
  void Initialize(int32_t min_id, int32_t max_id, int32_t begin_id) {
    if (begin_id < m_min_id || begin_id >= m_max_id) {
      begin_id = m_min_id;
    }

    m_has_use_num = 0;
    m_unique_id = begin_id - 1;
    m_min_id = min_id;
    m_max_id = max_id;

    int32_t id_num = max_id - min_id;
    int32_t byte_num = id_num / 8;
    if (id_num % 8 != 0) {
      ++byte_num;
    }
    m_use_bit_table = new uint8_t[byte_num];
    ::memset(m_use_bit_table, 0, byte_num);
  }

  void Destroy() {
    if (m_use_bit_table) {
      delete[] m_use_bit_table;
      m_use_bit_table = NULL;
    }
  }

  int32_t NewId() {
    std::lock_guard<LOCK> locker(m_mutex);

    if (m_has_use_num >= (m_max_id - m_min_id)) {
      return -1;
    }

    while (1) {
      m_unique_id++;
      if (m_unique_id < m_min_id || m_unique_id >= m_max_id) {
        m_unique_id = m_min_id;
      }

      int32_t byte_index = (m_unique_id - m_min_id) / 8;
      int32_t bitmask_index = (m_unique_id - m_min_id) % 8;

      if (!(m_use_bit_table[byte_index] & s_bitmask[bitmask_index])) {
        m_use_bit_table[byte_index] |= s_bitmask[bitmask_index];
        ++m_has_use_num;
        break;
      }
    }
    return m_unique_id;
  }

  void ReleaseId(int32_t unique_id) {
    if (unique_id < m_min_id || unique_id >= m_max_id) {
      return;
    }

    std::lock_guard<LOCK> locker(m_mutex);

    int32_t byte_index = (unique_id - m_min_id) / 8;
    int32_t bitmask_index = (unique_id - m_min_id) % 8;

    if (m_use_bit_table[byte_index] & s_bitmask[bitmask_index]) {
      --m_has_use_num;
      m_use_bit_table[byte_index] &= ~(s_bitmask[bitmask_index]);
    }
  }

private:
  LOCK m_mutex;

  int32_t m_has_use_num;
  int32_t m_unique_id;
  int32_t m_min_id;
  int32_t m_max_id;
  uint8_t *m_use_bit_table;

  static uint8_t s_bitmask[8];
};

template <typename LOCK>
uint8_t IdGenerator<LOCK>::s_bitmask[] = {0x80, 0x40, 0x20, 0x10,
                                          0x08, 0x04, 0x02, 0x01};

} // namespace utils
} // namespace common
