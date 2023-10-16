#include <iostream>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Add a numeric argument" << std::endl;
    return 1;
  }

  signed int counter{0};
  auto limit = atoi(argv[1]);

  for (int i = 0; i < limit; ++i) {
    std::cout << counter << std::endl;
    counter += counter + i; // possible overflow
  }

  std::cout << counter << std::endl;

  // unaligned read
  std::cout << *(char *)(&counter + 1) << std::endl;

  return 0;
}
