#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

// data race on a heap buffer with possible reallocation of memory
void vector_test() {
  std::vector<char> buf{'a', 'b'};

  auto t = std::thread([&] { buf.push_back('g'); });
  buf.push_back('x');

  std::cout << buf[2] << std::endl;
  t.join();

  std::cout << buf[2] << std::endl;
}

// data race on a stack variable
void int_test() {
  int buf = 10;
  auto t = std::thread([&] { buf += 10; });
  buf += 5;

  std::cout << buf << std::endl;
  t.join();

  std::cout << buf << std::endl;
}

// same as int_test, but std::atomic<int> is safe. No data race here.
void atomic_int_test() {
  std::atomic<int> buf = 10;
  auto t = std::thread([&] { buf += 10; });
  buf += 5;

  std::cout << buf << std::endl;
  t.join();

  std::cout << buf << std::endl;
}

int main(int argc, char *argv[]) {

  vector_test();
  // int_test();
  // atomic_int_test();

  return 0;
}
