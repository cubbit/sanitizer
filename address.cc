#include <iostream>
#include <memory>
#include <vector>

struct boh {
  std::shared_ptr<boh> boh_ptr;
  std::vector<char> buf;

  boh() : buf(1000, 'a') {}
};

void stack_buffer_overflow(int size) {
  char c = 0x42;
  char buf[256];

  std::cout << std::hex << (std::intptr_t)&c << std::endl;
  std::cout << std::hex << (std::intptr_t)&buf << std::endl;

  // buf[size] = 'a'; // write access

  // std::cout << buf[size] << std::endl; // read access
  std::cout << *(char *)(&c + 1) << std::endl; // read access
}

void heap_buffer_overflow(int size) {
  std::vector<char> buf(256);

  std::cout << std::hex << (std::intptr_t)buf.data() << std::endl;

  buf[size] = 'a';
  std::cout << buf[size] << std::endl;
}

void memory_leak() {
  auto boh1 = std::make_shared<boh>(); // boh_1 count = 1
  auto boh2 = std::make_shared<boh>(); // boh_2 count = 1
  boh1->boh_ptr = boh2;                // boh2 count = 2
  boh2->boh_ptr = boh1;                // boh1 count = 2
} // destructors of shared ptrs are called: both counts = 1 -> destructor of
  // inner boh is never called.

auto use_after_free() {
  auto pippo = std::string("pippo e' un mattacchione");
  return [&] { std::cout << pippo << std::endl; };
}

auto use_after_scope() {
  // auto pippo = std::array<int, 16>{0};
  int pippo = 3;
  return [&] { std::cout << pippo << std::endl; };
}

auto use_after_scope_2() {
  int *ptr;
  {
    int a = 10;
    ptr = &a;
  }
  std::cout << *ptr << std::endl;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Add a numeric argument" << std::endl;
    return 1;
  }

  int size = atoi(argv[1]);

  stack_buffer_overflow(size);
  // heap_buffer_overflow(size);
  // memory_leak();
  // use_after_scope_2();

  // use_after_free()();
  // auto broken_lambda = use_after_free();
  // auto broken_lambda = use_after_scope();
  // std::cout << "executing broken lambda" << std::endl;
  // broken_lambda();

  return 0;
}
