#include <dsb/dsb.h>
#include <iostream>

int main() {
  std::cout << "Hello World.\n";
  
  dsb::DSB *mydsb = new dsb::DSB("test");
  mydsb->Initialise();
  delete mydsb;
}
