/*
 * #include <stdio.h>
#include <utility>

int main() {
  std::move(1);
  return 1;
}*/

#include <event2/event.h>
#include <iostream>
#include <string>
#include <thread>
#include <libvirt/libvirt.h>

void timer_cb(evutil_socket_t fd, short what, void *arg)
{
  auto str = static_cast<std::string *>(arg);
  std::cout << *str << std::endl;
}

#define NUM_ALIGN_TOP(v, align) ((int)(((v) + (align - 1)) / (align)) * ((int)align))

int main()
{
  virConnectPtr conn;
  conn = virConnectOpen("qemu:///system");

  int i;
  int numDomains;
  int *activeDomains;
  numDomains = virConnectNumOfDomains(conn);
  activeDomains = (int*)malloc(sizeof(int) * numDomains);
  numDomains = virConnectListDomains(conn, activeDomains, numDomains);
  printf("Active domain IDs:\n");
  for (i = 0; i < numDomains; i++)
  {
    printf(" %d\n", activeDomains[i]);
  }
  free(activeDomains);

  int sum = 100 / 10 % 3;
  std::cout << "sum = " << sum << std::endl;

  auto t = NUM_ALIGN_TOP(15, 12);
  std::cout << "t = " << t << std::endl;

  auto task = []
  {
    std::cout << "task" << std::endl;
  };

  std::thread thread1(std::move(task));
  std::thread thread2(std::move(task));

  thread1.join();
  thread2.join();

  task();

  auto *base = event_base_new();

  struct timeval one_seconds = {1, 0};
  std::string str1 = "111 Hello, World!";
  auto *ev1 = event_new(base, -1, EV_TIMEOUT, timer_cb, (void *)&str1);
  event_add(ev1, &one_seconds);

  struct timeval five_seconds = {5, 0};
  std::string str2 = "222 Hello, World!";
  auto *ev2 = event_new(base, -1, EV_TIMEOUT, timer_cb, (void *)&str2);
  event_add(ev2, &five_seconds);

  event_base_dispatch(base);
  event_free(ev1);
  event_free(ev2);
  event_base_free(base);
  return 0;
}
