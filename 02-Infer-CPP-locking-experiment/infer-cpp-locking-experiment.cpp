#include <pthread.h>
#include <mutex>
#include <cstdio>

// thirdparty/boost/include/boost/interprocess/sync/posix/mutex.hpp
class posix_mutex {
  posix_mutex(const posix_mutex &);
  posix_mutex &operator=(const posix_mutex &);
  
  public:
    posix_mutex();
    ~posix_mutex();

    void lock();
    void unlock();

  private:
    pthread_mutex_t m_mut;
};

inline posix_mutex::posix_mutex() {
  pthread_mutex_init(&m_mut, NULL);
}

inline posix_mutex::~posix_mutex() {
  pthread_mutex_destroy(&m_mut);
}

inline void posix_mutex::lock() {
  //pthread_mutex_lock(&m_mut);
  printf("posix_mutex::lock() function\n");
}

inline void posix_mutex::unlock() {
  pthread_mutex_unlock(&m_mut);
}

// src/cpp/rtps/DataSharing/DataSharingListener.cpp
posix_mutex m;

void run() {
  std::unique_lock<posix_mutex> lock(m, std::defer_lock);
  int i = 0;
  while (i++ < 10) {
    lock.lock();

    lock.unlock();
  }
}

int main() {
  run();
}
