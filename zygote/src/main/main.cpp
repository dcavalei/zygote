#include <iostream>
#include "Zygote.h"
#include "syscall/nr.h"

int main() {
  std::cout << "Hello World" << std::endl;

  std::cout << __NR_read << std::endl;


  zyg::Zygote z;
  z.spawn();
  return 0;
}
