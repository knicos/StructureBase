#include <dsb/dsb.h>
#include <dsb/nid.h>
#include <iostream>
#include <string.h>

dsb::DSB *dsb::DSB::self_ = 0;

dsb::DSB::DSB(const char *dsbdir) {
  int length = 0;
  if (dsbdir != 0) length = strlen(dsbdir);
  if (length > 0) {
    dsbdir_ = new char[length];
    strcpy(dsbdir_, dsbdir);
  } else {
    dsbdir_ = 0;
  }
  initialised_ = false;
}

dsb::DSB::~DSB() {
  if (dsbdir_ != 0) delete [] dsbdir_;
  initialised_ = false;
  self_ = 0;
}

bool dsb::DSB::Initialise() {
  std::cout << "DSB Initialising... ";
  if ((self_ == 0) && (dsbdir_ != 0)) {
    initialised_ = true;
    self_ = this;
    std::cout << "success.\n";
    return true;
  }
  std::cout << "failed.\n";
  return false;
}
