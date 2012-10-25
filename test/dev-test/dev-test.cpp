#include <dsb/dsb.h>
#include <iostream>

int main() {
  std::cout << "Hello World.\n";
  dsb::Initialise();
  
  dsb::Finalise();
}
